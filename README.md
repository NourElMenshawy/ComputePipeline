# ComputePipeline 

This project is a minimal C++ implementation of a `ComputePipeline` that performs a series of transformations on an item to achieve a final result. The pipeline is designed to handle different types of input (e.g., files, URLs, or application bundle paths) and process them through a sequence of actions (e.g., decoding images, decompressing data, or parsing JSON).

## Overview

The `ComputePipeline` is responsible for:
1. Loading an item from storage based on a given URI.
2. Applying a series of transformations (actions) to the item.
3. Producing a final result after all applicable actions have been executed.

The pipeline supports extensible actions, and the processing logic is designed to minimize memory usage and avoid unnecessary copies.



## My Thought Process

### Understanding the Task
I began by thoroughly understanding the task requirements. The goal was to create a pipeline that processes an item through a series of transformations based on its type and metadata. I visualized the pipeline as a sequence of actions, where each action performs a specific transformation on the item.

### Key Design Goals
I identified three critical aspects for the pipeline:
1. **Functionality**: The pipeline should deliver its functionality by applying all possible transformations to the item.
2. **Safety**: The pipeline should remain safe during execution and item loading, ensuring no memory leaks or undefined behavior.
3. **Extensibility**: The pipeline should be easily extensible, allowing new actions to be added without modifying the core pipeline logic.

### Achieving the Goals
1. **Functionality**:
   - I designed the `Item` class to hold type-agnostic output data. The metadata helps the next action determine if it can process the item.
   - The pipeline executes actions sequentially, stopping when no more actions are applicable.

2. **Safety**:
   - All classes follow the **RAII (Resource Acquisition Is Initialization)** concept, ensuring that object lifetimes are managed explicitly.
   - Shared ownership between actions and the pipeline is expressed using `std::shared_ptr`, preventing memory leaks and ensuring safe resource management.

3. **Extensibility**:
   - I used the **type-erasure pattern** for the `Action` class instead of traditional polymorphism. This design allows new actions to be added easily, whether they are stateless or stateful.
   - **Type Erasure vs Virtual Functions**:
     - Type erasure provides better flexibility and avoids the overhead of virtual function calls.
     - It allows actions to be added without requiring a common base class.
     - It simplifies the addition of new actions, as they only need to satisfy the `ActionConcept` requirements.



## Key Components

### 1. `ComputePipeline`
- **Description**: The main class that orchestrates the loading and processing of items.
- **Functionality**:
  - Loads an item based on the provided URI.
  - Executes a sequence of actions on the item.
  - Stops processing when no more actions are applicable.
- **Methods**:
  - `addAction(Action action)`: Adds an action to the pipeline.
  - `execute()`: Executes the pipeline and returns the final processed item.
  - `loadItem()`: Loads the item from the specified URI.

### 2. `Action`
- **Description**: A type-erased class that represents a processing action.
- **Functionality**:
  - Encapsulates actions like decoding images, decompressing data, or parsing JSON.
  - Checks if an action can process a given item using `canProcess()`.
  - Processes the item using `process()`.
- **Concepts**:
  - `ActionConcept`: A concept that ensures an action type implements the required methods (`canProcess` and `process`).

### 3. `Item`
- **Description**: Represents the data being processed, along with metadata.
- **Functionality**:
  - Holds the output of each action and acts as the input for the next action.

### 4. `URI`
- **Description**: Represents the initial location of the item to be processed.
- **Supported Formats**:
  - File paths (`file://`)
  - URLs (`http://`, `https://`)
  - Application bundle paths (`bundle://`)

### 5. Example Actions
- **`DecodeImageAction`**: Decodes image data 
- **`DecompressAction`**: Decompresses compressed data 
- **`ParseJsonAction`**: Parses JSON data into a C++ object



## Setup and Build with CMake

### Prerequisites
- **CMake** (version 3.14 or higher)
- **C++ Compiler** (supporting C++20)

### Steps to Build and Run
1. Clone the repository:
   ```bash
   git clone https://github.com/NourElMenshawy/ComputePipeline.git
   cd ComputePipeline
   ```

2. Create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

3. Generate the build system using CMake:
   ```bash
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build .
   ```

5. Run the executable:
   ```bash
   ./compute_pipeline
   ```


## Performance Considerations
- The pipeline avoids unnecessary copying of data by using `std::shared_ptr` for items.
- Actions are executed in sequence, and the pipeline stops when no more actions are applicable.



## Resources 
- **Book**: *Hands-On Design Patterns with C++* by Fedor Pikus.
- **Talk**: [Type Erasure Implementation by Fedor Pikus](https://youtu.be/p-qaf6OS_f4?si=kApWNW39E4Av_k3S).



## Time Taken
The implementation of this project took approximately **5 hours**.


# Project Structure

The code of this project contains two main folders, one for **SUMO** and another for the **Agent**

# Architecture

This environment contains a Flask application which is the Agent and a Python application representing SUMO's interface. The choice of Flask for the Agent came from the necessity of having an available endpoint to send actions and rewards and receive actions. On the other hand, Sumo's interface only needs to work as a client of the Agent so it's not necessary to use Flask since it won't have any endpoints. The entrypoint of this application is the main.py that launches both SUMO and the Agent applications with a predefined simulation that uses the Mandelieu map.

## SUMO Architecture

This project contains the following components:

```
sumo_module
├───config
├───interface
├───services
├───simulation
├───tests
└───utils
```

### Component Description:

* **config**: general configurations of the project
* **interface**: contains all the logic to interact with the agent. This folder should include all the logic related to REST requests to the agent and the processing of the responses
* **examples**: contains map configurations for each scenario
* **services**: services logic to handle several operations in the simulation using traci and location of TraciConnector
* **simulation**: Mandelieu scenario simulation code and SUMO simulation initialization code
* **sumo installation**: sumo installations files
* **tests**: test folder for project's unit tests
* **utils**: general utilitary methods for the project

## Agent Architecture

This project contains the following components:

```
agent_ia_module
├───agent
├───routes
├───tests
└───utils
```

* **agent**: contains the agent class and related code
* **routes**: endpoint specification logic
* **tests**: test folder for project's unit tests
* **utils**: general utilitary methods for the project

# Adding a new scenario

To add a new scenario follow these steps:

1. Add new folder to examples folder containing the scenario files. The name of this folder is the identifier of the scenario that should be passed to the main.py script as an argument

2. Sumo and the Agent will receive the identifier of the scenario as an environment variable named "SCENARIO". This variable should be used to define the specific logic in both applications to run the scenario. An example of this can be seen in app.py script of SUMO

3. If the scenario contains specific configurations, create a settings.py file in the scenario folder and import the variables in the scenario's specific logic

# Installation

```shell
python main.py install # installs dependencies for the agent and sumo projects
```


It is possible that there are correspondence problems between the installed versions and the versions entered in the "requirements.txt". You can check this with the command
```shell
pip list
```
If so, run the command:
```shell
pip install -r requirements.txt
```

# How to run

The main.py script allows to start both the Agent and SUMO applications to run an example or just each of them individually. To run an example, a scenario must be provided:

```shell
# 2 scenarios : mandelieu or minimal
# To run an example providing a scenario in prod mode 
python main.py example --scenario mandelieu --mode prod

# To run an example providing a scenario in train mode 
python main.py example --scenario mandelieu --mode train

# To run an example providing a scenario in static mode 
python main.py example --scenario minimal --mode static

# To run example with default scenario (which is mandelieu)
python main.py example

# Only start Agent
python main.py agent

# Only start SUMO
python main.py sumo
```

# How to run tensorboard in navigator 

Run the commande : 
```shell
python -m tensorboard.main --logdir=runs/'file name'
```

If there is errors, run the comamnde : 
```shell
pip install standard-imghdr
```

# How to run the tests

The coverage report of the tests will be available at the htmlcov folder in the root folder. To inspect it you can simply open the index.html file in a browser of your choice.

```shell
# Runs agent tests with coverage report
python -m pytest -v --cov=agent_ia_module --cov-report=html agent_ia_module/app/tests/

# Runs sumo tests with coverage report
python -m pytest -v --cov=sumo_module --cov-report=html sumo_module/app/tests/

# Runs agent tests without coverage report
python -m pytest agent_ia_module/app/tests/

# Runs sumo tests without coverage report
python -m pytest sumo_module/app/tests/

# Run integration tests
python -m pytest integration_tests/ -v
```

# How to change the model save directory
Modify the parameters "MODEL_SAVE_DIR_PATH" in the file "default_settings.py"

# How use the model training (previously saved)
Modify the parameters "MODEL_LOAD_FILE_PATH" in the file "default_settings.py" for select the model file (*tar).
If you want to be in "Train" mode starting from a blank model, leave the parameter empty e.g.: r""

# How to use docker environment

In the root directory run the following commands:

```shell
# Runs Mandelieu scenario
docker compose --profile production build
docker compose --profile production up

# Runs unit tests
docker compose --profile unit-test build
docker compose --profile unit-test up

# Runs integration tests
docker compose --profile integration-test build
docker compose --profile integration-test up
```

# How to conduct an experiment

In the `./experiments` folder, you will find a documentation template to be completed before starting the training of your AI module.

Please follow the steps bellow :

1. Rename the file using the format : `DD_MM_YYYY.md`.

2. Indicate the experiment number for the day in the document title, using the format : `Experiment n°X`.

3. Fill in all the relevant information related to the experiment parameters.

# Gitlab notes

- The gitlab runner is limited in terms of network connections which creates problems when installing dependencies using pip. Therefore, I created the script **install-dependencies-for-gitlab.py** that downloads the dependencies locally so we can push them to the repo and the gitlab pipeline can use them. Whenever a requirements file is changed this script should be executed to ensure the dependencies are up to date.
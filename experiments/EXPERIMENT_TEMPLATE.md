## <p align="center">Expérience n°X</p>

<div align="center">
	<table>
		<tr><th colspan="6" align="center">La carte</th></tr>
        <tr>
          <td>Le nom du fichier</td>
          <td align="center"><!-- Nom de la carte --></td>
        </tr>
        <tr>
          <td>Nombre de feu</td>
          <td align="center"><!--  --></td>
        </tr>
        <tr><th colspan="6" align="center">Les hyperparamètres</th></tr>
        <tr>
          <td>Epsilon</td>
          <td align="center">0.99</td> 
        </tr>
        <tr>
          <td>Epoche</td>
          <td align="center">10000</td>
        </tr>
    </table>
</div>

<div align="center">
	<table>
		<tr><th colspan="6" align="center">Synthèse de l'expérience</th></tr>
        <tr>
          <td colspan="2">Avant l'expérience</td>
          <td colspan="4">"Project Structure
The code of this project contains two main folders, one for SUMO and another for the Agent

Architecture
This environment contains a Flask application which is the Agent and a Python application representing SUMO's interface. The choice of Flask for the Agent came from the necessity of having an available endpoint to send actions and rewards and receive actions. On the other hand, Sumo's interface only needs to work as a client of the Agent so it's not necessary to use Flask since it won't have any endpoints. The entrypoint of this application is the main.py that launches both SUMO and the Agent applications with a predefined simulation that uses the Mandelieu map.

SUMO Architecture
This project contains the following components:

sumo_module
├───config
├───interface
├───services
├───simulation
├───tests
└───utils



Component Description:


config: general configurations of the project

interface: contains all the logic to interact with the agent. This folder should include all the logic related to REST requests to the agent and the processing of the responses

examples: contains map configurations for each scenario

services: services logic to handle several operations in the simulation using traci and location of TraciConnector

simulation: Mandelieu scenario simulation code and SUMO simulation initialization code

sumo installation: sumo installations files

tests: test folder for project's unit tests

utils: general utilitary methods for the project


Agent Architecture
This project contains the following components:

agent_ia_module
├───agent
├───routes
├───tests
└───utils




agent: contains the agent class and related code

routes: endpoint specification logic

tests: test folder for project's unit tests

utils: general utilitary methods for the project


Adding a new scenario
To add a new scenario follow these steps:


Add new folder to examples folder containing the scenario files. The name of this folder is the identifier of the scenario that should be passed to the main.py script as an argument


Sumo and the Agent will receive the identifier of the scenario as an environment variable named "SCENARIO". This variable should be used to define the specific logic in both applications to run the scenario. An example of this can be seen in app.py script of SUMO


If the scenario contains specific configurations, create a settings.py file in the scenario folder and import the variables in the scenario's specific logic



Installation

python main.py install # installs dependencies for the agent and sumo projects


It is possible that there are correspondence problems between the installed versions and the versions entered in the "requirements.txt". You can check this with the command

pip list


If so, run the command:

pip install -r requirements.txt



How to run
The main.py script allows to start both the Agent and SUMO applications to run an example or just each of them individually. To run an example, a scenario must be provided:

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



How to run tensorboard in navigator
Run the commande :

python -m tensorboard.main --logdir=runs/'file name'


If there is errors, run the comamnde :

pip install standard-imghdr



How to run the tests
The coverage report of the tests will be available at the htmlcov folder in the root folder. To inspect it you can simply open the index.html file in a browser of your choice.

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



How to change the model save directory
Modify the parameters "MODEL_SAVE_DIR_PATH" in the file "default_settings.py"

How use the model training (previously saved)"</td>
        </tr>
        <tr>
          <td colspan="2">Pendant l'expérience</td>
          <td colspan="4"><!-- ... --></td>
        </tr>
        <tr>
          <td colspan="2">Après l'expérience</td>
          <td colspan="4"><!-- ... --></td>
        </tr>
    </table>
</div>
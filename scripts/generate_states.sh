# The states files describes the states of the engine, including:
# patient states, engine substance states, physiology states, and etc.
# The initial states files are needed by the sepsis progression program (howto-patientgeneration)
# For patient batch generation, after the patient definition file generation (bg-cli generate templates)
# The states need to be generated
cd ../runtime && bg-cli generate states
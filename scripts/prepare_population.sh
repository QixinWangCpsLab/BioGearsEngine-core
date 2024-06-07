cd ../runtime && bg-cli generate population config/population.template.xml
# NOTE, IMPORTANT:
# The result will be first saved to the location of runtime/patients/Patients_TIMESTAMP where
# TIMESTAMP is the current timestamp.
# But the engine will require all patient definition xml files to be located at the runtime/patients/ folder.
# So when you are ready to run the simulation, you need to move the generated patient definition xml files to the runtime/patients/ folder.
# Here we do not do the movement and deletion of the unneccessary folder and files for you
# in case that some unexpected error happens during the deletion process.
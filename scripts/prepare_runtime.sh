# after the installation, when we need to run the bg-cli or other programs based on the biogears, we
# need the runtime environments which contains some config files and definition files (such as the xsd)
# and substances and patients definition files, we need to generate them using the 
# interfaces provided by the biogears such as the bg-cli generate runtime etc.

# 1. Generate the runtime folfer in the project root folder
bg-cli generate runtime ../runtime
cp ../config/population.template.xml ../runtime/config/population.template.xml
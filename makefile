PDF = amplify-console-in-action.pdf
PDF_TRIAL = amplify-console-in-action-trial.pdf
PDF_EN = amplify-console-in-action-en.pdf

.PHONY: all clean;
all: 
prod: $(PDF);
trial: $(PDF_TRIAL);
en: $(PDF_EN);
clean:
	rm $(PDF) $(PDF_TRIAL) $(PDF_EN)

$(PDF): contents/* images/* catalog.prod.yml config.prod.yml
	docker-compose run -e ENV_NAME=prod -e LANG_NAME=jp --rm review && open $(PDF)

$(PDF_TRIAL): contents/* images/* catalog.trial.yml config.trial.yml
	docker-compose run -e ENV_NAME=trial -e LANG_NAME=jp --rm review && open $(PDF_TRIAL)

$(PDF_EN): contents/* images/* catalog.en.yml config.en.yml
	docker-compose run -e ENV_NAME=en -e LANG_NAME=en --rm review && open $(PDF_EN)


PDF = amplify-console-in-action.pdf
PDF_TRIAL = amplify-console-in-action-trial.pdf
PDF_EN = amplify-console-in-action-en.pdf

$(PDF):
	ln -f config.prod.yml config.yml && docker-compose run --rm review && open $(PDF)

trial:
	ln -f config.trial.yml config.yml && docker-compose run --rm review && open $(PDF_TRIAL)

en:
	ln -f config.en.yml config.yml && docker-compose run --rm review && open $(PDF_EN)

clean:
	rm $(PDF) $(PDF_TRIAL)

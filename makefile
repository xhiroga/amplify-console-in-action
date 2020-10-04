PDF = amplify-console-in-action.pdf
PDF_TRIAL = amplify-console-in-action-trial.pdf
PDF_EN = amplify-console-in-action-en.pdf

$(PDF):
	ENV_NAME=prod
	LANG_NAME=jp
	docker-compose run --rm review && open $(PDF)

trial:
	ENV_NAME=trial
	LANG_NAME=jp
	docker-compose run --rm review && open $(PDF_TRIAL)

en:
	ENV_NAME=en
	LANG_NAME=en
	docker-compose run --rm review && open $(PDF_EN)

clean:
	rm $(PDF) $(PDF_TRIAL)

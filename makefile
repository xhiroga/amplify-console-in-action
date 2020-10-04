PDF = amplify-console-in-action.pdf
PDF_TRIAL = amplify-console-in-action-trial.pdf
PDF_EN = amplify-console-in-action-en.pdf

$(PDF):
	docker-compose run -e ENV_NAME=prod -e LANG_NAME=jp --rm review && open $(PDF)

trial:
	docker-compose run -e ENV_NAME=trial -e LANG_NAME=jp --rm review && open $(PDF_TRIAL)

en:
	docker-compose run -e ENV_NAME=en -e LANG_NAME=en --rm review && open $(PDF_EN)

clean:
	rm $(PDF) $(PDF_TRIAL)

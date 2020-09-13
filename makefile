PDF = amplify-console-in-action.pdf

$(PDF):
	docker-compose run --rm review && open $(PDF)

clean:
	rm $(PDF)

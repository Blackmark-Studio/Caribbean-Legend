// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = NPCStringReactionRepeat("Lo siento, pero sería mejor para ambos si ya no nos habláramos más. Me castigarán a mí, y a ti te pedirán que te vayas.", "Ya te he contado todo, amigo. ¿O quieres que me azoten por tu culpa?", "No estoy escuchando...", "La espa-ada golpea y lát-tigo azota...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Aquí hay reglas muy duras...", "No, por supuesto, no lo quiero.", "¿Hmm...?", "Papá, ¿puedes oírme...?", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "CitizenNotBlade":
		dialog.text = "¡Capitán, ¿qué estás haciendo?! ¡Guarda tu arma antes de que te metas en muchos problemas!";
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "No te preocupes, estoy en ello...");
		link.l1.go = "exit";
		break;
	}
}

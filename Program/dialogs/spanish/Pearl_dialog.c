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
		dialog.text = "¡No tenemos nada de que hablar!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// ==> пиплы в поселении
	case "PearlMan":
		NextDiag.TempNode = "PearlMan";
		dialog.text = NPCStringReactionRepeat("¡Hola! Mi nombre es " + GetFullName(npchar) + ". ¿Qué puedo hacer por ti?", "¡Hola una vez más!", "Los visitantes son muy raros en este fin del mundo...", "¡Es un placer hablar con una cara nueva! Ya estoy enfermo de todas esas viejas trompas...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Oh, nada...", "Yo también...", "Ya veo...", "Je...", npchar, Dialog.CurrentNode);
		link.l1.go = "PearlMan_1";
		break;
	case "PearlMan_1":
		dialog.text = "Estamos recolectando perlas aquí, sirviendo a " + NationNameGenitive(sti(npchar.nation)) + ", ya sabes...";
		link.l1 = "Sí, lo sé...";
		link.l1.go = "exit";
		link.l2 = "Oye, escucha, ¿es posible comprar varios de estos pequeños adornos directamente del 'productor'? ¿Qué dirías?";
		link.l2.go = "PearlMan_2";
		break;
	case "PearlMan_2":
		if (rand(10) < 9)
		{
			dialog.text = "¡Oh no, por supuesto que no! ¡Un robo de incluso solo una pequeña perla se castiga con la muerte!";
			link.l1 = "Órdenes crueles tienes aquí, eso es seguro...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Sí, tenemos órdenes severas aquí, y uno puede perder fácilmente su cabeza por cualquier mala conducta. No me dedico a esto, pero puedo aconsejarte que hables con los indios locales sobre esto. Si algo sale mal, tienen a donde huir, así que deberían ser más audaces que nosotros...";
			link.l1 = "Ya veo... Bueno, gracias.";
			link.l1.go = "exit";
		}
		break;
	case "PearlMan_Sharp_1":
		dialog.text = LinkRandPhrase("¿Estás totalmente " + GetSexPhrase("loco? ¡Lárgate, idiota", "loca? ¡Lárgate, estúpida necia") + "!", "" + GetSexPhrase("¿¡Qué?! ¿Estás loco, idiota?", "¿¡Qué?! ¿Estás loca, idiota?") + " ¡Piérdete!", "" + GetSexPhrase("¿Has perdido la cabeza, querido? ¿Qué piratas? ¿Aquí? Simplemente lárgate, idiota", "¿Has perdido la cabeza, querida? ¿Qué piratas? ¿Aquí? Simplemente lárgate, idiota") + "...");
		link.l1 = RandPhraseSimple("No hay necesidad de ser grosero...", "¡Guarda tu lengua!");
		link.l1.go = "exit";
		break;

	// ==> индейцы в поселении
	case "IndPearlMan":
		NextDiag.TempNode = "IndPearlMan";
		dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Cara pálida", "Mujer blanca") + ", ¿quiere hablar?", "Tú de nuevo, " + GetSexPhrase("cara pálida", "blanca squaw") + ".", "" + GetSexPhrase("Cara pálida le gusta hablar. Parece una squaw.", "La squaw blanca disfruta hablando.") + "", "Los espíritus trajeron a cara pálida " + GetSexPhrase("hermano", "hermana") + " a mí.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sí.", "Sí, yo de nuevo.", "Muy poético.", "Estoy contento de verte también.", npchar, Dialog.CurrentNode);
		link.l1.go = "IndPearlMan_1";
		break;
	case "IndPearlMan_1":
		dialog.text = "Dime, ¿por qué has venido?";
		link.l1 = "Oh, nada en particular, solo quería escuchar lo que tienes que decir.";
		link.l1.go = "exit";
		break;

	case "CitizenNotBlade":
		dialog.text = "Capitán, ¿qué estás haciendo? ¡Guarda tu arma, antes de que causes muchos problemas!";
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "No te preocupes, ya la estoy guardando...");
		link.l1.go = "exit";
		break;
	}
}

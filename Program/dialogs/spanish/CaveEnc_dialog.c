// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "CaveBanditosSit":
		if (hrand(2) == 1)
		{
			dialog.text = NPCStringReactionRepeat("¡Vaya, mira quién está aquí! Bueno, hoy es tu día de suerte, compañero. Somos buenos tipos, ves, cocinando algo de comida y esas cosas... No te estoy invitando a nuestra cena, pero deberías perderte mientras aún puedas.", "Vete ya y no nos molestes. Vuelve mañana y no olvides traer tu bolsa contigo, ¡ja-ja-ja!", "¡No me hagas enfadar, marinero! ¿Todavía recuerdas dónde está la entrada a la cueva? Deberías ir allí ahora, muy, muy rápido...", "¡Bueno, ahora has cruzado la línea, compañero! ¡Supongo que tendré que alerjarme de mis asuntos y lidiar contigo, imbécil!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tan amable de tu parte, compañero...", "Veo que eres todo un bromista...", "Bien, sigue friendo tus tortillas, entonces...", "¡Ahora estamos hablando, ja-ja!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
		}
		else
		{
			dialog.text = LinkRandPhrase("¡Vaya, por los cielos! No hay necesidad de ir a cazar a la presa, ya está aquí... Oigan, chicos, vamos a sacudir a este petimetre, ¿verdad?", "Nadie te invitó aquí, compañero... Pero es muy bueno que estés aquí, de todos modos. Veamos ahora, ¡qué tan pesada es tu bolsa!", "Nadie te arrastró aquí a la fuerza, je-je... Pero si ya estás aquí, supongo que te haremos cosquillas un poco para ver qué cae de tus bolsillos...");
			link.l1 = LinkRandPhrase("Ahora haré tu lengua un poco más corta...", "¡Espero que tus habilidades con la espada sean tan buenas como tu ingenio, parlanchín!", "Bueno, parece que es hora de hacer un par de agujeros más en tu perecedero cuerpo...");
			link.l1.go = "fight";
		}
		NextDiag.TempNode = "CaveBanditosSit";
		break;

	case "CaveBanditosStay":
		dialog.text = LinkRandPhrase("¡Vaya, por los cielos! No hay necesidad de ir a cazar a la presa, ya está aquí... Oigan, chicos, vamos a sacudir a este petimetre, ¿verdad?", "Nadie te invitó aquí, compañero... Pero es tan bueno que estés aquí, de todos modos. Veamos ahora, ¡qué tan pesada es tu bolsa!", "Nadie te arrastró aquí a la fuerza, je-je... Pero ya que estás aquí, supongo que te haremos cosquillas un poco para ver qué cae de tus bolsillos...");
		link.l1 = LinkRandPhrase("Ahora voy a acortar un poco tu lengua...", "¡Espero que tus habilidades con la espada sean tan buenas como tu ingenio, parlanchín!", "Bueno, parece que es hora de hacer un par más de agujeros en tu perecedero cuerpo...");
		link.l1.go = "fight";
		break;

	case "CaveBanditosTreasure":
		dialog.text = NPCStringReactionRepeat("¡Piérdete, compañero! ¡No tienes nada que hacer aquí!", "Oye, te lo pido de buena manera: lárgate. Nunca se sabe lo que puede pasar...", "Última advertencia: si no te pierdes ahora mismo, lamentarás haber venido aquí.", "Eso es, compañero. Estás buscando problemas.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("No me digas qué hacer, ¿de acuerdo?", "¿Y qué hay de especial allí abajo? Solo una cueva, nada más...", "Oh, vamos ya...", "¡Ja! Bueno, veamos quién es mejor, ¡gusano!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
		NextDiag.TempNode = "CaveBanditosTreasure";
		break;

	case "CaveCaribSit":
		if (hrand(2) == 2)
		{
			dialog.text = NPCStringReactionRepeat("Cara pálida, vete. Él estará contento de que " + npchar.name + " sea amable. Los dioses tienen piedad de ti hoy.", "¡Sal de mi cueva, antes de que yo y mis hermanos nos enfademos!", "¡Lárgate, perro cara pálida!", "¡Tu suerte y vida se acaban, perro blanco!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bueno, gracias compañero, muy amable de tu parte...", "Esta cueva no es tuya, y voy donde quiero.", "Baja un poco el tono, engendro del pantano.", "Ahora voy a meterte estas palabras de vuelta en tu garganta, animal...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
		}
		else
		{
			dialog.text = LinkRandPhrase("¡Maldito rostro pálido, ha venido a nuestra fogata! ¡Uepa! ¡Estás acabado!", "Estúpido carapálida, ha venido a la guarida del jaguar. ¡Devoraré tu hígado!", "¿Insolente carapálida, se atreve a entrar en mi cueva? ¡Entonces nunca saldrá vivo!");
			link.l1 = LinkRandPhrase("Ahora arrancaré tu lengua...", "Ahora el mundo tendrá varios caníbales menos...", "Bueno, parece que es hora de hacer un par de agujeros más en tu caduco cuerpo, mono de cara roja.");
			link.l1.go = "fight";
		}
		NextDiag.TempNode = "CaveCaribSit";
		break;

	case "CaveCaribStay":
		dialog.text = LinkRandPhrase("¡El repugnante rostro pálido ha venido a nuestra cueva! ¡Whe-hee! ¡Voy a cortarte la lengua y freírla!", "Estúpido rostro pálido ha venido al guarida del jaguar. Hermanos, ¡cortad a este maldito perro blanco!", "¿Insolente cara pálida se atreve a venir a mi cueva? ¡Entonces nunca saldrá vivo!");
		link.l1 = LinkRandPhrase("Te cortaré la maldita cabeza...", "Ahora el mundo tendrá varios caníbales menos...", "Bueno, prepárate para encontrarte con tus ancestros, piel roja. ¡Al diablo contigo!");
		link.l1.go = "fight";
		break;

	case "exit_talk":
		DialogExit();
		sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
		for (i = 0; i < 4; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_CharacterDisableDialog(sld);
		}
		LAi_CharacterEnableDialog(npchar);
		break;

	case "fight":
		DialogExit();
		sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
		for (i = 0; i < 4; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, sGroup);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
		chrDisableReloadToLocation = true;
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
		{
			dialog.text = RandPhraseSimple("Hermanos, ¡hay un enemigo en las filas de la Inquisición!", "¡Levantad la alarma, hermanos!");
			link.l1 = "En efecto, los enemigos de la Inquisición están en alerta...";
			link.l1.go = "fight";
		}
		else
		{
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hola, " + GetSexPhrase("hijo mío", "hija mía") + ". ¿Qué te trae por aquí?..", "Me alegra verte en nuestra morada, " + GetSexPhrase("hijo mío", "hija mía") + ". ¿Qué te trajo aquí?"), "" + GetSexPhrase("Hijo mío", "Hija mía") + ", ya hemos hablado hoy. ¿Necesitas algo más?", "" + GetSexPhrase("Hijo mío", "Hija mía") + ", los acólitos de nuestra orden no son conocidos por su paciencia ilimitada. Así que, permíteme preguntarte una vez más: ¿hay algo que necesites?", RandPhraseSimple("Estás distrayendo a otros de sus deberes. No voy a hablar más contigo.", "" + GetSexPhrase("Hijo mío", "Hija mía") + ", no soy aficionado a las charlas sin sentido e inútiles. No voy a hablar contigo más."), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Solo pasé a saludar..", "Totalmente lleno de negocios..."), "¡Oh, no! Padre......", "No, padre, solo quería hablar...", RandPhraseSimple("¿Hmm...?", "Bueno, como desees, Padre..."), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "NoMoreTalkExit", npchar, Dialog.CurrentNode);
		}
		if (CheckAttribute(npchar, "protector.CheckAlways")) // гарды на камерах
		{
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "¡A las armas! ¡Es un espía! ¡Capturadlo!";
				link.l1 = "¡Caramba!";
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = LinkRandPhrase("Esta es una celda custodiada, y está estrictamente prohibido el acceso.", "No pienses siquiera en entrar, o serás castigado con la muerte.", "Solo un paso en esta celda, y estás acabado.");
				link.l1 = RandPhraseSimple("Ya veo, soldado.", "Lo entiendo...");
				link.l1.go = "exit";
			}
		}
		if (findsubstr(npchar.id, "Prisoner", 0) != -1) // заключенные
		{
			if (LAi_group_IsActivePlayerAlarm())
			{
				dialog.text = LinkRandPhrase("¡Ho-ho! ¡¿No es divertido ver a esos 'santos' yendo directamente al infierno?!", "¡Vaya! ¡¿Alguien realmente se atrevió a desafiarlos?!", "Me torturaron hasta casi la muerte, y moriré pronto, pero me has hecho feliz por última vez en mi vida...");
				link.l1 = RandPhraseSimple("¡Je!", "De nada...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Esos hipócritas son totalmente inhumanos. Arderán en el infierno por todo lo que nos han hecho...", "¡Me torturaban y atormentaban todos los días! ¡Pero no soy culpable ante los ojos de nuestro Señor!", "Mi compañero de celda murió ayer... Lo habían estado torturando en el potro durante dos días... Y quién sabe cuánto tiempo aguantaré yo...");
				link.l1 = RandPhraseSimple("Hmm... Bueno, no lo sé...", "Oh, ya veo...");
				link.l1.go = "exit";
			}
		}
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "NoMoreTalkExit":
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		break;
	}
}

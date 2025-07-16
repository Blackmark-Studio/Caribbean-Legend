void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	//--------------------------------- леди в резиденции ---------------------------------
	case "ResWoman":
		NextDiag.TempNode = "ResWoman";
		if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN)
		{
			link.chickengod = "Señora, por favor discúlpeme, pero me pidieron que le dijera que tiene... una cita dentro de una antigua pirámide pagana.";
			link.chickengod.go = "chickengod";
		}
		if (isBadReputation(pchar, 30))
		{
			dialog.text = LinkRandPhrase("¡Jesús! ¡Qué hombre tan despreciable en mis aposentos! ¡Apártate de aquí o llamaré a los guardias!", "Esto no puede estar ocurriendo... ¿Quién dejó entrar a esta rata en mi casa? ¡Sal de aquí, bastardo! ¡No tienes nada que hacer aquí! ¡Vete!", "Qué tiempos tan extraños han llegado. ¡Las ratas se están metiendo en mi dormitorio! ¡Vete!");
			link.l1 = RandPhraseSimple("Tranquilo...", "Cuida tu boca...");
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase("¿Qué estás haciendo en mi dormitorio? ¡Vete de aquí!", "¡Qué vergüenza! ¡Te pido que abandones este lugar de inmediato!", "Disculpe, señor, pero no ha sido invitado aquí. Por favor, ¡Salga de mi habitación!");
			link.l1 = RandPhraseSimple("Perdona... Me voy.", "Lo siento, puerta equivocada. Tengo que irme.");
			link.l1.go = "exit";
		}
		break;
	case "Woman_FackYou":
		dialog.text = "¡Oh!, ¿qué fue eso? ¡Soy un verdadero tonto! Caminando sin ver nada... ¡Guardias!";
		link.l1 = "¡Cállate!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
	//--------------------------------- слуга в резиденции ---------------------------------
	case "ResMan":
		NextDiag.TempNode = "ResMan";
		if (isBadReputation(pchar, 30))
		{
			dialog.text = LinkRandPhrase("¡Aléjate de aquí, rata!", "¡Aléjate inmediatamente de la hacienda del gobernador, rata!", "No me importa lo que estás haciendo en la casa del gobernador de " + XI_ConvertString("Colony" + npchar.city + "Gen") + "¡Pero mi consejo es que te pierdas, ahora!");
			link.l1 = RandPhraseSimple("Mantén la calma, amigo...", "¡Cuida tus palabras!");
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase("¡Saludos! Soy un sirviente del gobernador. Mi nombre es " + GetFullName(NPChar) + ".", "Vigilo este lugar, " + GetAddress_Form(NPChar) + ".", "Sabes, " + GetAddress_Form(NPChar) + ", nuestro gobernador es un buen hombre y nos paga bien...");
			link.l1 = RandPhraseSimple("Agradable.", "Hm, muy bien...");
			link.l1.go = "exit";
		}
		break;
	case "Man_FackYou":
		dialog.text = "¿¡Así que decidiste robar al gobernador?! ¡Guardias, atrapen al ladrón!!";
		link.l1 = "¡Cierra la boca!";
		link.l1.go = "fight";
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
	//--------------------------------- солдат в резиденции ---------------------------------
	case "ResGuard":
		NextDiag.TempNode = "ResGuard";
		if (isBadReputation(pchar, 30))
		{
			dialog.text = LinkRandPhrase("Más te vale alejarte de aquí, " + GetSexPhrase("colega", "chica") + "...", "¡Vete!", "¿Te equivocaste de puerta, " + GetSexPhrase("compadre", "chica") + "? Esta hacienda pertenece al gobernador de " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
			link.l1 = RandPhraseSimple("¡Me iré cuando quiera!", "No es asunto tuyo...");
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase("Hoy, me han ordenado servir aquí. Buen lugar...", "Protejo la finca de " + GetAddress_Form(NPChar) + ".", "Mi orden es proteger la hacienda del gobernador.");
			link.l1 = RandPhraseSimple("Buena suerte, entonces...", "Hmm, entiendo...");
			link.l1.go = "exit";
		}
		break;

	case "chickengod":
		pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
		if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3)
		{
			dialog.text = "Ah, sí. ¡Finalmente! Estoy listo para ir contigo, capitán.";
			link.l1 = "¿Así nomás? Señora, ¿está segura de que esto es lo que quiere?";
			link.l1.go = "chickengod_accept";
		}
		else
		{
			sld = CharacterFromID(npchar.city + "_Mayor");
			dialog.text = "¿¡Qué?! ¿Estás borracho, señor? ¡Qué broma tan idiota! Por favor, vete, te lo ruego!" + sld.name + "¡Guardias! ¡Ayuda!";
			link.l1 = "Mierda, es hora de irse.";
			link.l1.go = "chickengod_decline";
		}
		npchar.quest.chickengod = true;
		break;

	case "chickengod_accept":
		dialog.text = "¡Pues, claro! Ah, el Señor Aruba y yo hemos estado en una relación epistolar durante mucho tiempo!";
		link.l1 = "Ya que ese es el caso, ¡por favor sube a bordo!";
		link.l1.go = "chickengod_accept_take";
		link.l2 = "¡No, señora, eso no servirá. Mi honor no permitirá que se ponga en riesgo a una mujer, y claramente te han engañado!";
		link.l2.go = "chickengod_accept_nottake";
		break;

	case "chickengod_accept_take":
		DialogExit();

		pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
		pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
		AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;

	case "chickengod_accept_nottake":
		dialog.text = "En ese caso, mi querido capitán, toma tu sentido rural de honor y mételo en tu trasero! Esperaré a otro mensajero, alguien no tan estrecho de mente como tú!";
		link.l1 = "¡Encantador!";
		link.l1.go = "exit";

		pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
		SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;

	case "chickengod_decline":
		DialogExit();

		AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
	}
}

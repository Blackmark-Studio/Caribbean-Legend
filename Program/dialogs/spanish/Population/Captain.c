// Jason общий диалог праздношатающихся по улицам капитанов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// первая встреча
		if (npchar.quest.meeting == "0")
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY) // проверка межнациональных отношений
			{
				dialog.text = "¡Alto! Navegas bajo la bandera de " + NationNameGenitive(sti(pchar.nation)) + ", grumete. No tengo ningún deseo de hablar contigo y no quiero problemas... ¡Lárgate!";
				link.l1 = "Y te llamas a ti mismo capitán...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5) // боевые генераторные квесты 2015
			{
				dialog.text = "¡Ja! Llegas justo a tiempo, capitán... Tengo una propuesta de negocio para ti. ¿Tienes unas horas para mí?";
				link.l1 = "No. Tengo prisa, compañero. Quizás la próxima vez.";
				link.l1.go = "exit_quest";
				link.l2 = "Sí, puede que lo haga. Depende de lo que me ofrezcas. ¿Qué tal si vamos a la taberna a discutirlo?";
				link.l2.go = "march";
				break;
			}
			dialog.text = "¡Salud y buen encuentro! ¡Es bueno ver a un compañero capitán próspero!";
			link.l1 = "¡Me alegra verte, señor! Mi nombre es " + GetFullName(pchar) + "¿Tienes un minuto para hablar?";
			link.l1.go = "question";
			npchar.quest.meeting = "1";
		}
		else
		{
			// повторные обращения
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "¿Debería repetirlo? No quiero que sospechen que soy amigo de " + NationNameAblative(sti(pchar.nation)) + "¡Lárgate o llamaré a los guardias!";
				link.l1 = "Está bien, está bien, cálmate. Me voy.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "¿Qué quieres?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
		}
		NextDiag.TempNode = "First time";
		break;

	case "question":
		dialog.text = NPCStringReactionRepeat("" + GetFullName(npchar) + " a su servicio, buen señor! ¿Qué le gustaría saber?", "¡Encantado de hablar contigo, capitán!", "Bueno, supongo que tengo un minuto libre para hablar...", "Lamentablemente, tengo que irme. ¡Nos vemos!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("¿Tienes algo interesante que contarme?", "¿Tienes algo interesante que contarme?", "¿Tienes algo interesante que contarme?", "Claro. ¡Buena suerte!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;

		// квестовая часть
	case "march":
		dialog.text = "No, capitán, hay muchos ojos y oídos en las calles y en la taberna y no los necesitamos, créeme. Esta propuesta se trata de una... adquisición hostil de negocios, por así decirlo. Hablemos en mi barco.";
		link.l1 = "Está bien, morderé... ¿Cuál es tu barco y cómo se llama?";
		link.l1.go = "march_1";
		link.l2 = "¡Ja! Me suena sospechoso. Creo que no. ¡Adiós, señor!";
		link.l2.go = "exit_quest";
		break;

	case "march_1":
		// генерируем и запоминаем параметры в пчар, т.к. через нпчар не хочет нормально работать :(
		pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
		pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar) + 1;
		pchar.GenQuest.MarchCap.shiptype = SelectCaptainShipType();
		pchar.GenQuest.MarchCap.shipname = GenerateRandomNameToShip(sti(npchar.nation));
		pchar.GenQuest.MarchCap.nation = sti(npchar.Nation);
		pchar.GenQuest.MarchCap.model = npchar.model;
		pchar.GenQuest.MarchCap.rank = sti(npchar.rank);
		pchar.GenQuest.MarchCap.name = npchar.name;
		pchar.GenQuest.MarchCap.lastname = npchar.lastname;
		pchar.GenQuest.MarchCap.BaseNation = npchar.nation;
		pchar.GenQuest.MarchCap.Nation = hrand(NON_PIRATES);
		pchar.GenQuest.MarchCap.basecity = npchar.city;
		dialog.text = "Mi barco es " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Name"))) + " '" + pchar.GenQuest.MarchCap.shipname + "Está en el puerto ahora mismo. ¡No llegues tarde, capitán, me iré en seis horas!";
		link.l1 = "Entiendo, intentaré llegar a tiempo. ¡Nos vemos!";
		link.l1.go = "march_2";
		break;

	case "march_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
		npchar.lifeday = 0;
		pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
		pchar.quest.MarchCapOver.win_condition.l1.date.hour = sti(GetTime() + 6);
		pchar.quest.MarchCapOver.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.MarchCapOver.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.MarchCapOver.function = "MarchCap_Over";
		pchar.quest.MarchCap_Create.win_condition.l1 = "location";
		pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
		pchar.quest.MarchCap_Create.function = "MarchCap_Create";
		log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Escucha, como ciudadano de esta ciudad te pido que envaines tu espada.", "Escucha, como ciudadano de esta ciudad te pido que guardes tu acero.");
		link.l1 = LinkRandPhrase("Bien.", "Como desees.", "Como digas...");
		link.l1.go = "exit";
		break;

	case "exit_quest":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

int SelectCaptainShipType()
{
	int iClassFlag = FLAG_SHIP_CLASS_6;
	if (sti(pchar.rank) >= 19) iClassFlag = FLAG_SHIP_CLASS_2;	
	if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iClassFlag = FLAG_SHIP_CLASS_3;	
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iClassFlag = FLAG_SHIP_CLASS_4;
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iClassFlag = FLAG_SHIP_CLASS_5;
	if (sti(pchar.rank) < 5) iClassFlag = FLAG_SHIP_CLASS_6;
	
	return GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

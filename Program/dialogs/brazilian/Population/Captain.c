//Jason общий диалог праздношатающихся по улицам капитанов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
			if (npchar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Pare. Você navega sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+", marujo. Não quero conversar com você e não quero confusão... Cai fora!";
					link.l1 = "E você ainda se chama de capitão...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < COMPANION_MAX)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha! Chegou na hora certa, capitão... Tenho uma proposta de negócio pra você. Tem algumas horas pra mim?";
					link.l1 = "Não. Estou com pressa, amigo. Talvez outra hora.";
					link.l1.go = "exit_quest";
					link.l2 = "Talvez eu aceite. Depende do que você tem pra me oferecer. Que tal irmos até a taverna pra conversar?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Saudações e bem-vindo! É bom ver outro capitão próspero!";
				link.l1 = "Fico feliz em vê-lo, senhor! Meu nome é "+GetFullName(pchar)+". Você tem um momento para conversar?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Preciso repetir? Não quero que pensem que sou amigo de "+NationNameAblative(sti(pchar.nation))+"! Cai fora ou vou chamar os guardas!";
					link.l1 = "Tá bom, tá bom, calma. Eu já estou indo.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "O que você quer?";
					link.l1 = "Nada.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" às suas ordens, bom senhor! O que deseja saber?","Prazer em conversar com você, Capitão!","Bem, acho que tenho um minuto livre para conversar...","Infelizmente, preciso ir. Até mais!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Você tem algo interessante para me contar?","Tem algo interessante pra me contar?","Você tem algo interessante para me contar?","Claro. Boa sorte!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Não, capitão, há muitos olhos e ouvidos pelas ruas e na taverna, e não precisamos disso, pode confiar em mim. Essa proposta é sobre uma... tomada hostil de negócios, por assim dizer. Vamos conversar no meu navio.";
				link.l1 = "Certo, vou perguntar... Qual é o seu navio, e como ela se chama?";
				link.l1.go = "march_1";
				link.l2 = "Ha! Isso me soa suspeito. Acho que não. Adeus, senhor!";
				link.l2.go = "exit_quest";
			break;
			
			case "march_1":
				//генерируем и запоминаем параметры в пчар, т.к. через нпчар не хочет нормально работать :(
				pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
				pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar)+1;
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
				dialog.text = "Meu navio é "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" '"+pchar.GenQuest.MarchCap.shipname+"Ela está no porto agora mesmo. Não se atrase, capitão, vou partir em seis horas!";
				link.l1 = "Entendi, vou tentar chegar na hora. Até mais!";
				link.l1.go = "march_2";
			break;
			
			case "march_2":
			DialogExit();
				LAi_SetActorType(npchar);
				LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
				npchar.lifeday = 0;
				pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
				pchar.quest.MarchCapOver.win_condition.l1.date.hour  = sti(GetTime() + 6);
				pchar.quest.MarchCapOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.MarchCapOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.MarchCapOver.function = "MarchCap_Over";
				pchar.quest.MarchCap_Create.win_condition.l1 = "location";
				pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
				pchar.quest.MarchCap_Create.function = "MarchCap_Create";
				log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute, como cidadão desta cidade, peço que guarde sua espada.","Ouça, como cidadão desta cidade, peço que guarde sua espada.");
			link.l1 = LinkRandPhrase("Certo.","Como quiser.","Como você disser...");
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

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
					dialog.text = "Ahoi. Ihr segelt unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+", Schiffsjunge. Ich habe keinen Wunsch, mit dir zu reden, und ich will keine Probleme... Verzieh dich!";
					link.l1 = "Und du nennst dich einen Kapitän...";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//боевые генераторные квесты 2015
				{
					dialog.text = "Ha! Sie kommen gerade rechtzeitig, Kapitän... Ich habe ein Geschäftsangebot für Sie. Haben Sie ein paar Stunden für mich?";
					link.l1 = "Ich tue es nicht. Ich habe es eilig, Kumpel. Vielleicht das nächste Mal.";
					link.l1.go = "exit_quest";
					link.l2 = "Aye, das könnte ich. Es hängt davon ab, was du mir anbietest. Wie wäre es, wenn wir in die Taverne gehen, um zu diskutieren?";
					link.l2.go = "march";
					break;
				}
				dialog.text = "Sei gegrüßt und wohlgetroffen! Es ist gut, einen wohlhabenden Kapitän zu sehen!";
				link.l1 = "Freut mich, Sie zu sehen, Herr! Mein Name ist "+GetFullName(pchar)+". Haben Sie eine Minute zum Reden?";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Soll ich mich wiederholen? Ich möchte nicht als Freund verdächtigt werden von "+NationNameAblative(sti(pchar.nation))+"! Verschwinden Sie, oder ich rufe die Wachen!";
					link.l1 = "Gut, gut, beruhige dich. Ich gehe schon.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Was möchtest du?";
					link.l1 = "Nichts.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" zu Ihren Diensten, guter Herr! Was möchten Sie wissen?","Freut mich, mit Ihnen zu reden, Kapitän!","Nun, ich denke, ich habe eine freie Minute zum Reden...","Leider muss ich gehen. Auf Wiedersehen!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Haben Sie etwas Interessantes, das Sie mir erzählen können?","Haben Sie etwas Interessantes zu erzählen?","Haben Sie etwas Interessantes zu erzählen?","Sicher. Viel Glück!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "Nein, Kapitän, es gibt viele Augen und Ohren auf den Straßen und in der Taverne und wir brauchen sie nicht, glaub mir. Dieser Vorschlag handelt von einer... feindlichen Geschäftsübernahme, sozusagen. Lassen Sie uns auf meinem Schiff sprechen.";
				link.l1 = "Gut, ich beiße an... Wie heißt dein Schiff und ihr Name?";
				link.l1.go = "march_1";
				link.l2 = "Ha! Klingt verdächtig für mich. Ich denke nicht. Auf Wiedersehen, Herr!";
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
				pchar.GenQuest.MarchCap.Nation = drand(HOLLAND);
				pchar.GenQuest.MarchCap.basecity = npchar.city;
				dialog.text = "Mein Schiff ist "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" '"+pchar.GenQuest.MarchCap.shipname+". Sie liegt gerade im Hafen. Seien Sie nicht zu spät, Kapitän, ich werde in sechs Stunden weg sein!";
				link.l1 = "Ich sehe, ich werde versuchen pünktlich zu sein. Bis dann!";
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
			dialog.text = NPCharSexPhrase(NPChar,"Hör zu, als Bürger dieser Stadt bitte ich dich, deine Klinge zu verstecken.","Hör zu, als Bürger dieser Stadt bitte ich dich, dein Stahl wegzulegen.");
			link.l1 = LinkRandPhrase("Gut.","Wie du wünschst.","Wie du sagst...");
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
	int iClassFlag = FLAG_SHIP_CLASS_5;
	if (sti(pchar.rank) >= 19) iClassFlag = FLAG_SHIP_CLASS_2;	
	if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iClassFlag = FLAG_SHIP_CLASS_2;	
	if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iClassFlag = FLAG_SHIP_CLASS_3;
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iClassFlag = FLAG_SHIP_CLASS_4;
	if (sti(pchar.rank) < 5) iType = iClassFlag = FLAG_SHIP_CLASS_5;
	
	return GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

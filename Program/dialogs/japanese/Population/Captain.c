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
					dialog.text = "止まれ。お前は～の旗の下で航海しているな "+NationNameGenitive(sti(pchar.nation))+"、小僧。俺はお前と話す気はねえし、面倒ごともご免だ……さっさと失せろ！";
					link.l1 = "それで自分を船長と呼ぶのか……";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < COMPANION_MAX)//боевые генераторные квесты 2015
				{
					dialog.text = "はっ！ちょうどいい時に来たな、船長……お前に商談があるんだ。俺に少し時間をくれないか？";
					link.l1 = "知らねえよ。急いでるんだ、相棒。次の機会にな。";
					link.l1.go = "exit_quest";
					link.l2 = "ああ、そうかもな。何をくれるか次第だぜ。酒場で話でもしようじゃねえか？";
					link.l2.go = "march";
					break;
				}
				dialog.text = "やあ、ご機嫌よう！また一人、繁盛している船長に会えて嬉しいぜ！";
				link.l1 = "お会いできて嬉しいです、旦那！私の名前は "+GetFullName(pchar)+"。少しお話しする時間はありますか？";
				link.l1.go = "question";
				npchar.quest.meeting = "1";
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "もう一度言わなきゃならないのか？俺があいつの仲間だなんて疑われたくねえんだ。 "+NationNameAblative(sti(pchar.nation))+"「消え失せろ、さもないと衛兵を呼ぶぞ！」";
					link.l1 = "わかった、わかった、落ち着け。俺はもう行く。";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "何の用だ？";
					link.l1 = "「何もない。」";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" お仕えいたしますぜ、旦那！何をお知りになりたいんで？","お話できて嬉しいぜ、船長！","まあ、話す時間が少しはあると思うぜ…","残念だが、俺は行かなくちゃならねえ。またな！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("俺に何か面白い話でもあるか？","俺に何か面白い話でもあるのか？","俺に何か面白い話でもあるか？","ああ。幸運を祈るぜ！",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
		break;
		
		//квестовая часть
			case "march":
				dialog.text = "いいえ、船長、街や酒場には見張りや耳がたくさんいますし、奴らは必要ありません、信じてください。この提案は、 いわば……敵対的な商売の乗っ取りについてなんです。私の船で話しましょう。";
				link.l1 = "よし、乗ってやるよ……お前の船はどんな船で、名前は何ていうんだ？";
				link.l1.go = "march_1";
				link.l2 = "はっ！怪しい話だな。俺は遠慮しとくぜ。じゃあな、旦那！";
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
				dialog.text = "俺の船は "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype),"Name")))+" 「」"+pchar.GenQuest.MarchCap.shipname+"。今は港にいるぞ。遅れるなよ、船長、俺は六時間後には出発するからな！";
				link.l1 = "なるほど、時間に間に合うようにするぜ。じゃあな！";
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
			dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、この町の市民として頼む、剣を納めてくれ。","聞いてくれ、この町の市民として頼む、剣を収めてくれ。");
			link.l1 = LinkRandPhrase("結構だ。","ご希望の通りに。","おっしゃる通りで……");
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

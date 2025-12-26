//navy
#include "DIALOGS\%language%\Common_Duel.c" 
// boal 29.05.04 даем карту клада
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	aref   item;
	bool   ok;
	
	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	ProcessDuelDialog(NPChar, link, Diag); //navy
	bool bPesosMap = Statistic_AddValue(PChar, "Treasure", 0) < 3;
	int iTreasureMapPesosCost = TreasureMapPesosCost();

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
            dialog.Text = "安心しな、あんたはきっと金持ちになれるぜ。布でもハンカチでも、好きなもんで包んでやるよ。";
			Link.l1 = "そこで待ってろ、すぐ戻るからな！";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "しっ…こっちに来い…お前に面白い話があるんだぜ…";
			Link.l1 = "何の話だ？";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "酒でもどうだ！ひっく……一緒に飲もうぜ！";
    			Link.l1 = "ああ、黙れよ。本気かと思ったぜ。";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "手頃な値段であんたに渡したい物があるぜ。";
    			Link.l1 = "「それは何だ？」";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "ああ、どっか行けよ。こんなことで俺の時間を無駄にさせるな。";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "これは素晴らしい地図だぜ。こんなもん、どこの店にも置いてねえよ。宝の隠し場所が記されてるんだ。 俺自身じゃそこに行けねえが、この地図は本物だ、誓ってもいい。";
			Link.l1 = "それは面白いな。いくら欲しいんだ？";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "「ああ、消え失せろ。こんなことで俺の時間を無駄にさせるな。」";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "たった "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "わかった。それと、きれいな布で包んでくれ。";
				if (sti(pchar.money) >= iTreasureMapPesosCost) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			else
			{
				dialog.Text = "「たったの」 "+NPChar.TreasureMoney+" ドゥブロン金貨。"; // Addon-2016 Jason
				Link.l1 = "わかった。それと、きれいな布で包んでくれ。";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "高すぎるな。いらねえよ。";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "ほらよ。これでお前も金持ちだぜ！";
			Link.l1 = "ありがとう！";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "一杯やろうぜ、どうだ？ひっく……ここのラムは最高だ！";
			Link.l1 = "時間がないんだ！";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "「お前、俺に偽物の地図を売りやがったな！」";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "「お前は誰だ？ひっく！知らねえし、どうでもいいぜ！」";
			Link.l1 = "気にするな……";
			Link.l1.go = "exit";
			Link.l2 = "てめえ、こんな偽物を売りつけやがって！ぶっ飛ばしてやるぞ…";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

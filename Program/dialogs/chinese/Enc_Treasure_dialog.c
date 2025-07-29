//海军
#include "DIALOGS\%language%\Common_Duel.c" 
// boal 29.05.04 给予藏宝图
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

	ProcessDuelDialog(NPChar, link, Diag); //海军

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();			
		break;

        case "Map_NotBuy":
			dialog.Text = "我向你保证, 你会发财的。 如果你愿意, 我可以用布和手帕把它包起来。 ";
			Link.l1 = "待在这儿, 我马上回来! ";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "嘘... 听着... 我有好东西要给你... ";
			Link.l1 = "你在说什么? ";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
				dialog.Text = "来杯酒! 嗝... 和我一起喝! ";
				Link.l1 = "哦, 闭嘴。 我还以为你是认真的。 ";
				Link.l1.go = "exit";
            }
            else
            {
				dialog.Text = "我有个好东西要以合理的价格卖给你。 ";
				Link.l1 = "会是什么呢? ";
				Link.l1.go = "map_treasure_2";
				Link.l2 = "哦, 走开。 我没时间搭理这个。 ";
				Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
			dialog.Text = "这是一张很棒的地图。 你在任何商店都买不到这样的东西。 它标明了宝藏的隐藏地点。 我自己去不了那里, 但这张地图是真的, 我发誓。 ";
			Link.l1 = "很有意思, 你想要多少钱? ";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "哦, 走开。 我没时间搭理这个。 ";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			dialog.Text = "只要" + Pchar.GenQuest.TreasureMoney + "杜布隆。 "; // Addon-2016 Jason
			Link.l1 = "好吧。 用一块漂亮的布把它包起来。 ";
			if (PCharDublonsTotal() >= sti(Pchar.GenQuest.TreasureMoney)) // Addon-2016 Jason
			{
			   Link.l1.go = "map_treasure_buy";
			}
			else
			{
			   Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = "太贵了。 我不需要。 ";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
			dialog.Text = "给你。 现在你要发财了! ";
			Link.l1 = "谢谢! ";
			Link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(sti(Pchar.GenQuest.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // 卖完就跑, 如果是决斗, 他的生命会延长
		break;
		
		case "Temp_treasure":
			dialog.Text = "我们喝一杯吧, 好吗? 嗝... 这里的朗姆酒很棒! ";
			Link.l1 = "我没时间! ";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
				Link.l2 = "你卖给我的是假地图! ";
				Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
			dialog.Text = "你是谁? 嗝! 我不认识你, 也不在乎! ";
			Link.l1 = "算了... ";
			Link.l1.go = "exit";
			Link.l2 = "你卖给我的是假货! 我要揍扁你... ";
			Link.l2.go = "outraged"; //海军  —决斗!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // 以免退出时消失
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "tavern_keeper":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
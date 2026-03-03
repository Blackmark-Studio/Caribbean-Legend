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
            dialog.Text = "장담하건대, 부자가 될 거요. 원한다면 천이나 손수건에 싸서 드리리다.";
			Link.l1 = "거기 가만 있어, 금방 돌아올게!";
			Link.l1.go = "exit";
		break;
		
		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = "쉿... 이리 와서 들어봐... 너한테 흥미로운 게 있어...";
			Link.l1 = "무슨 소리를 하는 거야?";
			Link.l1.go = "map_treasure_1";
		break;
		
		case "map_treasure_1":
            ok = GetCharacterItem(Pchar, "map_part1") > 0 && GetCharacterItem(Pchar, "map_part2") > 0;
            if (!CheckAttribute(NPChar, "TreasureMoney") || GetCharacterItem(Pchar, "map_full") > 0 || ok)
            {
                dialog.Text = "술 한잔 어때! 히익... 나랑 한잔 하자!";
    			Link.l1 = "아, 닥쳐. 진지한 줄 알았잖아.";
    			Link.l1.go = "exit";
            }
            else
            {
                dialog.Text = "적당한 값에 줄 물건이 있어.";
    			Link.l1 = "그게 뭔데?";
    			Link.l1.go = "map_treasure_2";
    			Link.l2 = "아, 꺼져. 나 이런 데 쓸 시간 없어.";
    			Link.l2.go = "exit";
			}
		break;
		
		case "map_treasure_2":
            dialog.Text = "훌륭한 지도야. 이런 건 어떤 가게에서도 절대 못 구하지. 보물 숨겨진 곳이 표시되어 있어. 나 스스로는 갈 수 없지만, 이 지도는 진짜야, 맹세해.";
			Link.l1 = "흥미롭군. 얼마를 원하는 거지?";
			Link.l1.go = "map_treasure_3";
			Link.l2 = "아, 꺼져. 나 이런 데 쓸 시간 없어.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_3":
		    if (npchar.quest.trade_date != lastspeak_date)
		    {
                npchar.quest.trade_date      = lastspeak_date;
            }
			if(bPesosMap)
			{
				dialog.Text = "단지 "+FindRussianMoneyString(iTreasureMapPesosCost)+"."; // Addon-2016 Jason
				Link.l1 = "알겠어. 그리고 좋은 천으로 잘 싸 줘.";
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
				dialog.Text = "단지 "+NPChar.TreasureMoney+" 두블룬."; // Addon-2016 Jason
				Link.l1 = "알겠어. 그리고 예쁜 천으로 잘 싸 줘.";
				if (PCharDublonsTotal() >= sti(NPChar.TreasureMoney)) // Addon-2016 Jason
				{
				   Link.l1.go = "map_treasure_buy";
				}
				else
				{
				   Link.l1.go = "Map_NotBuy";
				}
			}
			Link.l2 = "너무 비싸. 필요 없어.";
			Link.l2.go = "exit";
		break;
		
		case "map_treasure_buy":
            dialog.Text = "여기 있어. 이제 부자가 되겠네!";
			Link.l1 = "고마워!";
			Link.l1.go = "exit";
			if(bPesosMap) AddMoneyToCharacter(pchar, -iTreasureMapPesosCost);
			else RemoveDublonsFromPCharTotal(sti(NPChar.TreasureMoney));// Addon-2016 Jason
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
		break;
		
		case "Temp_treasure":
            dialog.Text = "한잔 하자고, 어때? 히끅... 여기 럼주 끝내주게 내오거든!";
			Link.l1 = "시간 없어!";
			Link.l1.go = "exit";
            if (GetCharacterItem(Pchar, "map_full") == 0)
            {
				Achievment_SetStat(68, 1); // ugeen 2016
    			Link.l2 = "너 나한테 가짜 지도를 팔았잖아!";
    			Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;
		
		case "Temp_treasure_1":
            dialog.Text = "너 누구야? 힉! 난 너 모르겠고, 신경도 안 써!";
			Link.l1 = "신경 쓰지 마...";
			Link.l1.go = "exit";
			Link.l2 = "이 위조품을 나한테 팔았잖아! 아주 혼쭐을 내주겠어...";
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

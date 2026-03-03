// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、なんでもありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "ふむ……で、モリガンはどこだ？自分で俺に会いたいって言ってたんじゃねえのか？";
				link.l1 = "可哀想なポールは熱を出しているんだ。\n彼は取引する気分じゃない。\n代わりに私が来た。";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "何の用だ、旦那？";
				link.l1 = "鉄木を買いに来たってわけか？";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "誰がそんな戯言を言ったんだ、旦那？私は誰も何も待っていない。 私の船はウィレムスタッド総督の命令でこの周辺を巡回しているんだ。だから、悪いが私の船から降りてくれ、 君は何か勘違いしているはずだ。";
			link.l1 = "ふむ……そうか。ご迷惑をおかけして申し訳ありません。";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "もうこの話はしたんじゃねえか、旦那？";
			link.l1 = "はいはい。もう出発して、自分の船に乗り込むところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "「お前は誰だ？」";
			link.l1 = "誰と取引するか気にしないのか？鉄の木を持ってきたんだ。いくらで買う？";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "取り決め通り――一つにつき四十ドゥブロンだ。";
			link.l1 = "ふむ……";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "相棒、俺たちはモリガンと取引したんだぜ。これはいい値段だ、これ以上のは見つからねえよ。 だから市場の百姓みたいにごねるな。鉄木はどれくらい持ってるんだ？";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "素晴らしい。期待以上だ。ほら、金貨を受け取れ。もしさらにアイアンウッドを手に入れたら、 サン・マルタンの酒場に行って……例の人物に話しかけろ。奴が俺たちの会合を手配してくれる。 お前はあの間抜けなモリガンよりずっと頼りになる相棒だな。";
				link.l1 = "いいだろう。取引成立だ。";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "よし。ほら、金貨だ。もし鉄木をもっと手に入れたら、フィリップスバーグの酒場に行って……あいつに話せ。誰のことかわかるだろう。そいつが俺に連絡を取る。お前とは、 あの間抜けなモリガンと同じくらい商売ができそうだな。";
				link.l1 = "いいだろう。取引成立だ。";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "ふむ……もっと期待していたんだが。まあいい。ほら、金貨だ。次は必ず百枚以上持ってこいとモリガンに伝えておけ。";
				link.l1 = "わかった。私が彼に伝えよう。";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "ふざけてるのか？モリガンとは取引があったんだぞ、ロットは五十個未満じゃダメだ！さっさと失せろ、 十分揃うまで戻ってくるんじゃねえ。";
			link.l1 = "わかった、わかった、落ち着け。";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "おお、古い友よ！鉄木を売りに来たのか？";
			link.l1 = "その通りだ、マイケル。取引しよう。";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "どれくらい持ってるんだ？俺が必要なのは、それより少なくない量だぞ "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "それは知っている。俺にはある "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  お前がそんなに欲しがっている鉄木のことだ。";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "うーん。残念だが、そんなに持っていないんだ。";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "くそっ、警告されなかったのか？それともネズミが木を食っちまったのか？俺は必要なんだ "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" 一片たりとも足りなくては困る。次回は、私の代理人が指示した通りの木材を持ってくるのだ。\nもう二度と私を失望させないでほしい、さもなくば君の仕事を断らざるを得なくなるぞ。";
				link.l1 = "わかりました、旦那。これからはもっと注意します。";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "お前、これで二度目だぜ。気に入らねえ。これが最後の警告だ、次はお前の頼みなんざ断るからな。";
					link.l1 = "くそっ、ネズミどもが俺の商品を台無しにしやがった！約束するぜ、ミシェル、こんなことはこれが最後だ。";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "もう我慢の限界だ！これ以上お前と取引したくねえ。とっとと失せろ、そして俺のことは忘れろ。";
					link.l1 = "「でも旦那…」";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "おったまげたぜ！すまねえな、旦那、だが俺が買えるのは "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+"、お前の積み荷全部を買うだけの金は持っていないんだ。俺はある品の入荷を期待していたんだが "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" …1枚あたり40ドゥブロンの金貨で…";
				link.l1 = "わかった。持っていけ "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" 今はここまでだが、残りは次の機会に売ってやるぜ。";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "承知した。値段はいつも通り、一つにつき四十ドゥブロンだ。";
				link.l1 = "俺は構わねえ。お前の分を持っていけ。";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "お取引できて光栄です。また鉄木を売りたくなったら、ぜひ私のところへ来てください。";
			link.l1 = "また会おう、旦那。おかげで俺はずいぶん儲かったぜ。じゃあな！";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

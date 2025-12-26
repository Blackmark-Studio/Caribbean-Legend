void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "これはバグだ。開発者に知らせてくれ。";
			link.l1 = "ああ、いいぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "瓶を持ってきたか？";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "ああ、そうだ。俺はそれに七百ペソ払ったから、お前には千ペソもらうぜ。";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "いや、今取り組んでいるところだ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "神に感謝だ、喉がカラカラだったんだよ。ありがとう、旦那！ほら、千枚受け取ってくれ、俺はこのボトルをもらうぜ、 はは！さて、せっかくいい取引をしてるんだ、もう一つ頼みがあるんだ\n俺と仲間たちの……将来のために、もっとワインを用意してくれないか？ちょうど密輸団から金を巻き上げたばかりで、余裕があるんだよ、 へへ……";
			link.l1 = "悪いな、相棒、もう一度酒を取りに行く暇なんてねえんだ。";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "金はいつでも歓迎だぜ。何本欲しいんだ？";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "ご希望通りに。ともかく助けてくれてありがとう！乾杯、そして君の健康に！";
			link.l1 = "いいぞ、その調子で頑張れ、兵士！";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "一本につき八エスクード銀貨1000枚なら、六十本までは買えるが、それ以上は無理だ。\nだが、十本未満は持ってくるなよ――それじゃ余計に喉が渇くだけだぜ！";
			link.l1 = "承知した、60本を超えず、10本を下回らないようにする。あんたのワインを持ってくるぜ。";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "良き酒の知らせを運ぶ足は祝福される！頼りにしてるぜ、船長。ああ、忘れるところだった！ 酒は一週間以内にここへ持ってきてくれよ。うちの海兵中隊は七日後に艦隊へ異動になるんだ。 出発したら数ヶ月は戻らねえからな。\n";
			link.l1 = "なるほど。急いでみるぜ。";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "それで、船長、ワインは持ってきたのか？";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "ああ、あるぜ。";
				link.l1.go = "Wine_take";
			}
			link.l2 = "いいや。まだ作業中だ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "聖アルヌルフよ、我らのために祈りたまえ！\nすごい量のワインだな！素晴らしい！\n残念ながら、先ほど申し上げた通り、我々が買えるのは六十本だけだ。あいにく、これ以上買う金がないんだ。\nペソを受け取ってくれ、この六十本は大事に預かるよ。残りは取っておいてくれ。";
				link.l1 = "ありがとう。君とその兵隊仲間たちで、俺の健康を祝って一杯やってくれよ！";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "おかえり。さて……持ってきたのは "+sti(pchar.questTemp.Wine.Qty)+" 瓶か。いいね！もらっていくぜ。支払いは "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "ありがとう。君とその兵隊仲間たちで、必ず俺の健康を祝って一杯やってくれよ！";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "もちろんだぜ。 "+GetAddress_Form(NPChar)+"！太鼓が集合の合図を鳴らしてる、俺はもう行かなくちゃ。じゃあな！";
			link.l1 = "順風満帆で行けよ、相棒！";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

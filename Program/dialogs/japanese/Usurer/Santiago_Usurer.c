// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","どのようなご用件でしょうか？"),"あなたはその質問を少し前にも私に尋ねようとしましたね…","ああ、さては……また同じことをぐるぐる繰り返してるんじゃないか？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ご明察の通りです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "旦那、俺は船長だ "+GetFullName(pchar)+"、そして私はルーカス・ローデンブルクからの使いでここに来た。彼からあなたへの荷物を預かっている。";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "ルーカス・ローデンブルグ旦那の返事をもらいに来た。";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "想像してみろよ……荷物だぜ！さあ、渡してくれ、旦那。";
			link.l1 = "「それから、ローデンブルグ旦那がこれをあなたに渡してほしいと頼まれました…」";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "私の知る限り、船長、荷物以外にも受け取るはずの物があったはずです。\nそれで…それはどこにありますか？私が何のことを言っているのかお分かりでしょうか？";
			link.l1 = "もちろんでございます！宝箱は私の船で厳重に保管しております。すぐにお届けいたします。";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "ふむ……興味深いですね。つまり彼は「遺憾の意を示している」と。なるほど、なるほど。とはいえ、 ローデンブルク旦那の遺憾の意はなかなか説得力がありますから、否定しがたいですね。旦那、 きちんとした返事を書くには少し時間がかかりますので、明日の正午ごろにまたお越しいただけますか？ そのときに返事をお渡しします。\n酒場で休むもよし、町を散策するもよし。サンティアゴには見どころがたくさんありますよ。";
			link.l1 = "わかった、明日の正午ごろにまた来る。では、その時に会おう、旦那。";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "はい、もちろん……ですが、書面での形式にはこだわらなくてもよろしいかと存じます。\nただ彼にこう伝えてください――「この男は死なねばならない」と。それが公正でしょうし、受け取った謝罪の「価値」を考えれば問題も生じません。\nこれで一件落着と見なされます。";
			link.l1 = "わかった、覚えておくよ、旦那。ほかに何かあるか？";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "はい、もちろんです。私が申し上げたことはジラルディ家の意志でございます。そして、 もちろんルーカス旦那に私の最上のご挨拶をお伝えいただけます。順風をお祈りします、船長。 "+GetFullName(pchar)+".";
			link.l1 = "承知しました。では、旦那、お元気で "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

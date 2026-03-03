// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？","何を知りたいんだ？"),"何の用だ、 "+GetAddress_Form(NPChar)+"?","「それで三度目だな、お前が俺に聞こうとしたのは……」","もううんざりだ、消え失せろ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("悪いが、気が変わったんだ。","なんでもねえ、悪かったな。"),"忘れてしまった、すまねえ…","三度目の正直だな、え？失礼するぜ…","すまん、すまん！じゃあ、俺はこれで失礼するぜ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "ごきげんよう。サンティアゴの異端審問官、ヴィンチェント神父が手紙であなたのことに触れていた。 あなたが私を助けてくれるかもしれないと言っていたよ。";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "「ヴィンチェント神父から何か知らせはあるか？」 "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "パドレ・ヴィンチェントに会う必要がある。彼が興味を持っていた品を見つけたんだ。";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "「それで、」 "+npchar.name+"、パドレ・ヴィンチェントは何を話したんだ？";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ああ、旦那。パドレ・ヴィンチェント自身があんたと取引するなんて、相当な名のあるお方に違いねえな。";
			link.l1 = "素晴らしい。じゃあ、お前が使い走りってわけだな。さて、よく聞け、 この男はヴィンチェント神父にとって非常に重要な人物だ。今からお前の責任下にある。サンティアゴまで連れて行くか、 誰か代わりを見つけるんだ。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "異端審問官の代理として囚人の管理を任されているんだ。手錠は外さない方がいいぞ、 ガイウス・マルシェは力のある男だからな。\nこの手紙をヴィンチェント神父に渡して、二日以内に返事を待っていると伝えてくれ。これで十分だと思うが、どうかな。 ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "了解だ、旦那。できる限りやってみるぜ。神父様を手伝うのはこれが初めてじゃねえからな。";
			link.l1 = "それだけじゃねえ。サン・グレゴリオ号の船長、カルロス・ゲバラがここに来たはずだ。 俺にバニラを持ってきてくれることになってたんだ。俺の手紙をお前に渡してくれたか？";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "ああ、荷は無事で、旦那を待ってるぜ。";
			link.l1 = "よし、それじゃあ俺の船に積み込ませるぜ。パドレ・ヴィンチェントの返事を待って、ここに二日間滞在するつもりだ。 今はまだお別れじゃねえぞ。 "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "ああ、旦那。こちらがヴィンチェント神父からの手紙だ。神父はあんたにとても満足してるぞ、 あとのことは手紙を読めばわかるさ。";
			link.l1 = "素晴らしい。それまでだな、 "+npchar.name+"。さて、今はこれで失礼するぜ。";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "わかった。それを俺に渡せば、聖父のもとへ届けてやる。";
			link.l1 = "無理だぜ、兄弟！あれを手に入れるのは簡単じゃなかったんだ。そう簡単には渡さねえよ。 パドレ・ヴィンチェント本人にしか渡さないからな。";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "「でも旦那！どうやってあんたが俺をだましてないって分かるんだ？」";
			link.l1 = "見てくれ：香炉、聖杯、それからラズライト付きの十字架だ… "+npchar.name+"「俺が誰だと思ってるんだ？まさか、あいつらなしで異端審問に行くほど馬鹿だと思ってるのか？」";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "許してくれ、旦那……明日また来てくれれば、ヴィンチェント神父にあんたの到着を伝えるぜ。";
			link.l1 = "よし。明日また会おう。";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "閣下がお会いになるぞ、旦那。訪問は早めにな。これが書類だ、衛兵に見せれば中に入れてくれる。ただし、 まずスペインの旗を掲げろよ、でないと兵士たちに捕まるかもしれねえからな。";
			link.l1 = "了解だ。スペイン語だな。ありがとう、相棒！これから向かうぜ！";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

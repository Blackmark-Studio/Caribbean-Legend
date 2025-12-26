// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「全ての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしてたんだぜ。お前、忘れちまったのか…","これで三度目だな、俺にちょっかい出すのは……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、もしかしたら次の機会にな。","そうだな、なぜか忘れちまったんだ…","「ああ、本当にこれで三度目だな……」","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "エンリケ・ゴンザレスを探してるんだ。彼の居場所を教えてもらえねえか？";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "ゴンザレス旦那のことは誰でも知ってるぜ！あいつの家は港役所の隣だ。";
			link.l1 = "「彼はいくつだ？」";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "そうだな、はっきりとは言えねえが、少なくとも五十歳には見えるぜ。あの家にはもうずいぶん長く住んでるんだ。 海賊についての大げさな話をよくするが、どうせ夢の中でしか会ったことねえ連中のことだろうよ。";
			link.l1 = "どうやらあいつが俺の探していた男みたいだ。ありがとう、 "+npchar.name+"、本当に助かったぜ！";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

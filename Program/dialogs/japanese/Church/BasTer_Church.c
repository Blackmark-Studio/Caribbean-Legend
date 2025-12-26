// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いている、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば何でも言ってくれ。","「聖職者にはやることが山ほどあるんだ、お前は邪魔してるぞ」 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は違うんだ、神父……"),"申し訳ないが、俺から言うことは何もねえ。","後で聞くぜ。すまねえ、神父様。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "神父様、ちょっと変わった件で参りました。最近、 ガイ・マルシェという私掠船乗りが貴教区にとても貴重な品を献上したそうですね。金の胸十字架で、 ラズライトがはめ込まれていたとか。本当ですか？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ああ、そうだ、息子よ！これは我が教区で最も素晴らしい品だ。こんなに見事なものは生涯見たことがない！\nだが、なぜ尋ねるのだ、息子よ？なぜこの十字架に興味があるのだ？";
			link.l1 = "聖父様、これはお気に召さないでしょうが、この十字架は他の教区から盗まれ、その際に聖職者が殺害されました。\nこの品をあなたに差し出した男は殺人者です。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "我々は皆罪を犯すのだ、息子よ、そして聖職者を殺したというのは重大な告発だ。何か証拠はあるのか？ この十字架はどこの教区から盗まれたのだ？";
			link.l1 = "俺の言葉じゃ証拠にならねえのか？この十字架はサンティアゴの教区から盗まれたもんだ、必ず返さなきゃならねえんだ。 ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "サンティアゴ？それはスペインの都市じゃないか？息子よ、お前には驚かされるな……";
			link.l1 = "聖父様、神の前では誰もが平等です。スペイン人も我々と同じくキリスト教徒であり、 国同士の争いが信者の心に影響を与えてはなりません。どうかこの十字架をサンティアゴ教区にお戻しくださいますよう、 お願いいたします。";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "息子よ、この十字架が我らの教区のために敬虔なキリスト教徒たちから贈られたものだと分からないのか？！いや、 息子よ、お前の頼みは聞けない。";
			link.l1 = "この十字架のために血が流されたことを気にしねえのか？聖職者の血だぜ、スペイン人だろうが関係ねえ。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "息子よ、何の証拠も示しておらんし、わしはお前の言葉を鵜呑みにするわけにはいかん。 十字架は我らの教区に留めておく。これがわしの最終決定じゃ。\nそれに、この件でスペイン人を助けようとするお前の行動には大いに心を痛めておる。";
			link.l1 = "そうか。では、さらばだな、神父様……";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

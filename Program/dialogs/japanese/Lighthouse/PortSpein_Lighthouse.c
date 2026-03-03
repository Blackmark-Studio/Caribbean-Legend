// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？","何を知りたいんだ？"),"「何か用か、」 "+GetAddress_Form(NPChar)+"?","「それで三度目だぜ、俺に聞こうとしたのは…」","もううんざりだ、消え失せろ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("悪いが、気が変わったんだ。","たいしたことじゃねえ、悪かったな。"),"忘れてしまった、すまねえ…","三度目の正直ってやつだな、え？失礼するぜ…","すまん、すまん！じゃあ、俺はこれで失礼するぜ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "聞いてくれ、ミゲル・ディチョソ指揮のフリゲート艦が1654年4月頃この辺りにいたんだが、その後姿を消したんだ。彼の船について何か知ってるか？何があったのか、 どこへ行ったのか見たことはないか？何か覚えていることはあるか？";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "おおっと……ああ、旦那、あれは本当に見事だったぜ！あんな光景は忘れられねえよ、はは！";
			link.l1 = "何が起きたのか教えてくれないか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ディチョソ旦那のフリゲート艦がサンホセの港に錨を下ろしたんだ。俺は全部しっかり見てたぜ、ああ。 あれは見事なフリゲートだった、まさに傑作だ、俺の血の通った心臓に誓ってもいい！ 乗組員たちはその速さを自慢してたよ、最高で十六ノットも出るってな！ここに一日滞在してから、 トバゴ島へまっすぐ出航したんだ。そしたら信じられねえことに、やつらが地平線の向こうに消えた途端、 天気がおかしくなり始めたんだよ。それまで何日も晴れが続いてて、一片の雲もなかったのによ！なのに、 いきなりひでえ嵐が現れたんだ。まるでネプチューン様ご本人が来たみてえだったぜ！ 俺は灯台のてっぺんまで登って火を灯そうとしたんだが、そこで見ちまった……サンタ・キテリアだ！巨大な波に乗って、でっけえ竜巻を従えて現れたんだ！ フリゲートは火花みてえに俺の灯台をかすめて、嵐に押されて北西へ吹き飛ばされた！それ以来、 サンタ・キテリアを見た者はいねえ。たった一時間後には、風も雨も雲も消えて、太陽が輝いてた。 嵐の痕跡なんてひとつもなかったぜ！あんなの見たことねえ！でもその日は湾で琥珀を山ほど拾ったんだよな……\n";
			link.l1 = "じゃあ、嵐でフリゲート艦がカリブ海まで押し戻されたのか？";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "ああ、そうだ！ずっと向こうのマルティニークまで流されたんだ。あの嵐でディチョソが生き残れたとは思えねえが、 奴も必死だったぜ！フリゲートは沈んじゃいなかったが、サンタ・キテリア号は今ごろサンゴの間で海の底だろうな……実はな、ディチョソとあのフリゲートについて聞いてきたのはあんたが最初じゃねえんだ。";
			link.l1 = "本当か？他にミゲルに興味を持ってた奴は誰だ？";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "スペイン艦隊の、なかなかの切れ者の船長だったぜ！名乗ったのは……ああ……すっかり忘れちまった……あっ！ディエゴ旦那だ。名前はディエゴだったが、姓は……デ・モンターニャかデ・モントーヤだったかな。そんな感じだ。お前と同じように俺の話を聞いて、 礼を言って去っていった。それっきり一度も見てねえな。";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "なるほど。お話を聞かせてくれて本当にありがとう、すごく助かったぜ。感謝の気持ちにコインを受け取ってくれ。 じゃあな。";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "なるほど。お話を聞かせてくれて本当にありがとう、おかげで大いに助かったぜ。じゃあな。";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、用件は何だ？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はその質問を持ち出すのはこれで三度目ですよ……","聞け、ここは店だ。人々はここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったんだ……","「ええ、本当にこれで三度目ですね……」","ふむ、俺はしないぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "聞いてくれ、俺はちょっと洒落た服が必要なんだ。高いやつだ、ちゃんとした貴族みたいに見せたいんだよ。そういうの、 何かあるか？";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "「アドミラブル」という名のガレオン船が最近あなたに皮革の積荷を運んできました。覚えておられますか？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "貴族の服かい？もちろん、ここに一揃いあるよ。ズボン、ジャーキン、絹のシャツ、それにブーツだ。値段は2万ペソさ。この服はとても質が高くて、着心地も抜群、見た目も素晴らしいから、これより安くはできないよ。";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "よし！渡してくれ。";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "うーん……今はそんなに金がないんだ。";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "金が用意できたらまた来てくれ。";
			link.l1 = "わかった。すぐ戻るぜ！";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "「はい、どうぞ。」";
			link.l1 = "ありがとうございます！";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "はい。彼は時間通りに到着し、商品を降ろして、私は約束通り代金を支払いました。 なぜそんなことをお聞きになるのですか？";
			link.l1 = "あの船の船長はガイウス・マルシェ、私の古い知り合いです。だから彼を探しているのです。\nその後、彼がどうしたか教えていただけませんか？もしかして追加の貨物を渡したとか、 行き先を話していたとかありませんか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "そんなことはないよ。俺はあいつに貨物の話なんて一切してないし、向こうからも頼まれなかった。 将来の計画なんて何も聞かされてない。細かいことなんて覚えちゃいないよ、 あれからここに何人出入りしたと思ってるんだ？あいつは荷を降ろして、さっさと出航した――それだけしか言えないね。";
			link.l1 = "わかった。まあ、とにかくありがとう。幸運を祈る！";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

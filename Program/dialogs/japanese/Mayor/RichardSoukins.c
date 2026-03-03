// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "俺に用でもあるのか？ないなら、とっとと失せろ！";
			link.l1 = "もう行くぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "俺にやらせる仕事はあるか？";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "足取りは掴んだが、奴を巣穴からおびき出すには金がいる――三万ペソ用意しろ。";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "ほら、これを見ろ。密輸業者の死体から見つけた手紙だ";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "終わったぜ。ノーマン・ヴィーゴと奴の船は海の悪魔の元へ行っちまった。";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "ふん…仕事が欲しいってか？まあ、聞いてくれてちょうど良かったぜ。外部の人間が必要なんだ。 近くの町でちょっと調べたいことがあるが、俺の手下どもは顔が割れてる。大した報酬は約束できねえが、何かはやるぜ。 ";
			link.l1 = "いいじゃねえか！任務はなんだ？";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "悪いが、そんな端金のために危険は冒さねえ。じゃあな。";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "じゃあ聞け、俺は一ヶ月前にスクーナー船『セイントブルー』の船長と奴隷二百人を届ける取引をしたんだ。 地元のプランテーションの主に売るつもりだった。もう期限は過ぎて、依頼主が心配し始めたが、 昨日になってそのスクーナーが島の近くで目撃されたと聞いた。だがな！船長は現れなかった。今日になって、 依頼主は前金を返せと要求してきたうえに、別の売り手から奴隷を買う話を持ちかけられたと言いやがった。 値段は高いが、奴隷全員を一度に手に入れられるってな。";
			link.l1 = "それで？お前の前金を失わないために、数日で奴隷を200人も探せってのか？たったの小銭のためにかよ？";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "当たり前だろ。俺がバカに見えるか？前金なんざ返す気はねえよ。ただ、 あいつに渡された奴隷が俺のもんだって証拠が必要なんだ。新しい取引を持ちかけた奴らを見つけろ、そしたら1万ペソやるぜ。どうだ？";
			link.l1 = "乗ったぜ。何か心当たりはあるか？誰がやったと思う？";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "無理だな。他を当たれ。たった一万か？悪いが、それじゃ話にならねえ。";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "もし俺に何か考えがあったら、お前の助けなんざ絶対に借りねえよ。あいつらはとっくにくたばってるはずだ。だがな、 奴らがどうやって『セイントブルー』の積み荷と俺の依頼人のことを知ったのか、俺は知りたくてたまらねえ。 どうやら奴らにとっちゃ、ずいぶん簡単だったらしいな。わかったか？";
			link.l1 = "ああ、誰かがお前を裏切ったんだ。";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "その通りだ！俺はそいつを探してるんだ。俺の競争相手を殺したり、 奴隷を取り戻したりするのはお前の優先事項じゃねえ。俺が欲しいのはあのネズミ……いや、正直言えば、串刺しにしたあいつの首だ。\nこれでわかっただろ、なぜ俺の部下どもにお前の任務を一切知らせちゃいけねえか？ 誰が情報を売ってやがるのか突き止めるまで、俺は全員を疑うつもりだ。そして、 できればそんなことはしたくねえんだよ……";
			link.l1 = "なるほど。じゃあ、目立たないようにするぜ。これから向かう。";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "三万だと？大金じゃねえか…今出せるのは五千ペソだけだ、それしか持ってねえ。金を持ち逃げするなんて考えるんじゃねえぞ、 見つけ出して一番近い柵に吊るしてやるからな！わかったか？";
			link.l1 = "よし、じゃあ五千払えよ……";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "受け取れ。お前の探索の結果を待ってるぜ。";
			link.l1 = "全部うまくいくぜ。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "ははっ！素晴らしい知らせだな！お前ならやれると確信してたぜ。面白い情報があるんだ。";
			link.l1 = "仕事は終わったぜ、だから一万払えよ。";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "ああ、これが報酬だ。だが逃げるなよ、もう一つ頼みがあるんだ。\nパイファーはノーマン・ヴィーゴの部下で、ルガー船『セプティマ』の乗組員だ。 ノーマン・ヴィーゴは俺たちの仲間の一人でも、間違いなく裏切り者だ。最近、この島の近くの海域で目撃されている。 このネズミを海の悪魔の元へ送るのがお前の仕事だ。前回はしくじらなかったから、今回も頼みたい。報酬は15,000ペソ払う。どうだ？";
			link.l1 = "任せとけ！裏切り者ノーマン・ヴィーゴは死んだも同然だぜ。";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "なあ、俺はそれに関わりたくねえんだ…どうせ時間もねえしな。悪いが、俺は行くぜ。";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "分かってる、分かってるぜ。俺の部下が戦いを見張ってて、お前の完璧な勝利をもう報告してきた。よし、 仕事はきっちりやったな。約束通り1万5千ペソだ。感謝するぜ、大いに助かった。";
			link.l1 = "大丈夫だ、手伝えてよかったぜ！だがもう行かねえと、ここに長居しすぎたし、やることが山ほどあるんだ。じゃあな！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}

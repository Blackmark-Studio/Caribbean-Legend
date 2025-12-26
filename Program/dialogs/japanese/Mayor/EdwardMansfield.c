// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"！俺は "+GetFullName(NPChar)+"、このクソ溜めの新しい総督だ。地元のチンピラどもを従わせるのは簡単じゃねえが、 もうスペイン領植民地への脅威にはならねえ。";
					Link.l1 = "お会いできて嬉しいぜ。俺は船長だ "+GetFullName(Pchar)+"。悪いが、俺は行かなきゃならねえ。";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+"。俺は忙しいんだ、本当に忙しい。スペイン植民地への脅威を防ぐために、 地元のチンピラどもを抑えておかねえといけねえんだ。";
					Link.l1 = "じゃあ、邪魔はしねえよ。";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("俺に話すことはあるか？ないのか？じゃあ "+GetSexPhrase("ここから失せろ！","俺の邪魔をするんじゃねえぞ。")+"","俺の言いたいことははっきり伝わったはずだが……","はっきり言ったはずだが、まだ俺をイライラさせるつもりか！","まあ、お前は比べ物にならねえな "+GetSexPhrase("あまりにも無礼だぜ、坊や","なんて無礼なんだ、娘","なんて無礼なんだ、娘")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("俺は行くぜ。","「ああ」 "+npchar.name+"、そういうことか。","「悪いな」 "+npchar.name+"...","いてっ…",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


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
								link.l2 = "足取りは掴んだが、ネズミを巣穴からおびき出すには金がいる――三万ペソ用意しろ。";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "ほら、これを見ろ。密輸業者の死体から見つけた手紙だ";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "終わったぜ。ノーマン・ヴィーゴと奴の船は海の悪魔のものになった。";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "ふん…仕事が欲しいってか？まあ、ちょうどいい。俺には外部の奴が必要なんだ。近くの町でちょっと調べたいことがあるが、 俺の手下どもは顔が割れてる。大した報酬は約束できねえが、何かはやるぜ。";
			link.l1 = "任務は何だ？";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "悪いが、そんなはした金のために危険は冒さねえ。じゃあな。";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "じゃあ聞け、俺は一ヶ月前にスクーナー船『セイントブルー』の船長と200人の奴隷を届ける取引をしたんだ。地元のプランテーションの主に売るつもりだった。締め切りは過ぎて、 依頼主が心配し始めたが、昨日になってそのスクーナーが島の近くで目撃されたと聞いた。だがな！船長は現れなかった。 今日になって依頼主は前金を返せと要求してきて、他の売り手から奴隷を勧められたと言ってきた。値段は高いが、 奴隷を一度に全部手に入るらしい。";
			link.l1 = "それで？お前の前金を失わないために、たった数日で奴隷を200人も集めろってのか？小銭のためにだと？";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "当たり前だろうが。俺がバカに見えるか？前金なんざ返す気はねえよ。だが、 あいつに持ちかけられた奴隷が本当に俺のものだって証拠が必要なんだ。新しい取引を持ちかけた連中を見つけてこい、 そしたら1万ペソやるぜ。どうだ？";
			link.l1 = "乗ったぜ。誰がやったか心当たりはあるか？";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "無理だな。他を当たれ、たった一万か？悪いが、それじゃ話にならねえ。";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "もし俺に何か考えがあったら、お前なんかに頼んだりしねえよ。あいつらはとっくに死んでるはずだ。だがな、 奴らがどうやって『セントブルー』の積み荷と俺の依頼人のことを知ったのか、俺は知りたくてたまらねえ。 どうやら奴らには簡単なことだったらしいな。わかったか？";
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
			dialog.text = "その通りだ！俺はそいつを探してるんだ。俺の競争相手を殺したり、 奴隷を取り戻したりするのはお前の優先事項じゃねえ。俺が欲しいのはあのネズミ――いや、正直言えば、串刺しにしたあいつの首だ。 これで俺の手下どもにお前の任務のことを絶対に知られちゃいけねえ理由が分かっただろ？ 誰が情報を売ってやがるのか突き止めるまで、俺は全員を疑うぜ。……それは俺も本当は望んじゃいねえがな。";
			link.l1 = "なるほど。じゃあ、目立たないようにするぜ。これから向かう。";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "三万だと？大金じゃねえか…今あるのは五千ペソだけだ、それしか渡せねえ。金を持ち逃げしようなんて考えるなよ、 見つけ出して一番近い柵に吊るしてやるからな！わかったか？";
			link.l1 = "よし、じゃあ五千払えよ……";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "受け取れ。お前の探索の結果を待っているぞ。";
			link.l1 = "大丈夫だ。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "ははっ！いい知らせだな！お前ならやると思ってたぜ。面白い情報があるんだ。";
			link.l1 = "仕事は終わったぜ、俺の一万をよこせ。";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "「ああ、これが報酬だ。だが逃げるんじゃねえぞ、もう一つ頼みがあるんだ。\nファイファーはノーマン・ヴィーゴの手下で、ラガー船『セプティマ』の乗組員だ。 ノーマン・ヴィーゴこそが裏切り者だと俺は確信してる、たとえ奴が俺たちの仲間でもな。最近、 あの島の近くの海域で目撃されている。このネズミを海の悪魔に送るのがお前の仕事だ。 前回はちゃんとやってくれたから、今回も頼みたい。報酬は一万五千ペソだ。どうだ？」";
			link.l1 = "任せとけ！裏切り者はもう死んだも同然だぜ。";
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
			dialog.text = "わかってる、わかってるぜ。俺の部下が戦いを見張ってて、お前の完璧な勝利はもう報告済みだ。よし、 仕事はきっちりやったな。約束通り、1万5千ペソだ。感謝するぜ、大いに助かったよ。";
			link.l1 = "大丈夫だ、助けになれてよかったぜ！だが、もう行かねえといけねえ。ここに長く居すぎたし、 やることが山ほどあるんだ。じゃあな！";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "挨拶しよう、俺の名はアリステア・グッドだ。マンフィールドの死後、バッカニアの頭に選ばれたんだ。";
			link.l1 = "はじめまして、Alistair。";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "俺はお前と話してる暇なんかねえ。後で来い。";
			link.l1 = "俺はもう行くぜ。";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Get","Get")+" 出て行け！","俺の家から出ていけ！");
			link.l1 = "おっと…";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "俺にかまうな、覚えとけよ。";
        			link.l1 = "わかったぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

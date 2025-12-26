// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんなご質問でございますか、」 "+GetSexPhrase("若い男","お嬢さん")+"?","「ご用件は何ですの」 "+GetSexPhrase("「ハンサム」","可愛い子")+"？どうぞ、お聞きください。"),"また質問ですの","うふふ、もしよろしければ――ご質問をどうぞ…",""+GetSexPhrase("ふむ、ご自分の好みの美女を選んではいかが？あなたのこと、ちょっと怪しく思えてきましたわ……","ふふん、ご自分の好みの美女を選んでみてはいかが？残念ながら、ここには男の子はいないのよ、うふふ……")+"","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わりました、失礼します。","実は、やっぱりいいわ。"),"わたくし……失礼いたしました、今のところ質問はございませんわ。","おっしゃる通り、もう三度目ですね。失礼いたしました。","「また今度にしましょう、マダム。」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "聞いてくれ、オーロラ。今夜は女の子が必要なんだ。それに、家に連れて帰りたいんだが、手配できるか？";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "もちろんですわ、旦那様。もうお好みの乙女を見つけられましたの？それとも、わたくしがご案内いたしましょうか？";
			link.l1 = "ええ、そうですわ。ルシールという名の娘に目をつけておりますの。";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "「ルシール・モンテーニュのことをおっしゃっているのですか？」";
			link.l1 = "正直に言うと、彼女の名字は聞かなかったんだ。知っているのは、 ルシールという名の若くて美しい金髪の娘だということだけさ。";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "ええ、まさに彼女のことをよく表していますわ。\nさて、それで……でも、どうして彼女なのです？他の娘たちはお気に召しませんの？";
			link.l1 = "ええとですね……彼女はここで働き始めたばかりですから、「商売」の経験もまだ浅いと思いますの。ですから、 私のお財布にあまり負担にはならないでしょう。";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "ご覧の通り、私は色白のブロンドが大好きなのですわ。ルシールなら、その点で完璧ですわね。";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "まあ旦那、それは違いますわ！あの子は若くて美しくて、しかも経験豊富ですのよ。お客様方はみんな彼女に夢中ですわ。 一晩ご一緒するには高くつきますの。五千ペソでございます、それより一ペソもまけられませんわ。";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "高いけれど、まあいいでしょう。こちらがあなたのコインですわ。";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "高いな！そんなに持ってないぜ。また後で話そう。";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "はあ、旦那、あなたの言う通りですわ。あの子は可愛くて若いけれど、まだ経験が足りませんの。 お客様方も普段はあまり彼女に目を留めませんから、こうしてお尋ねしたのですわ。でも、 もし本当に控えめな娘がお好きなら、あの子は良い選択ですわ。料金は二千五百ペソでございます。";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "ああ、彼女で十分だろう。金貨を受け取れ。";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "高いな！そんなに持ってないぜ。また後で話そう。";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "あんたが最初ってわけじゃないよ、イケメンさん。時には彼女のために客が列を作ることもあるんだ。 うちの島の褐色の娘たちとはまるで違うからね。彼女は四千五百ペソになるよ。";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "高いけれど、まあいいわ。お金を受け取ってちょうだい。";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "高いな！そんなに持ってねえよ。また後で話すぜ。";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "本当ですの、旦那？もうホームシックでいらっしゃるの？うちのクレオール娘たち、特にムラートたちは、 こののんびりしたパリの路地猫よりずっと情熱的ですのよ。でも、あいにく、それはあなたのご自由ですわ。 あの子は三千ペソいただきますわ。";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "高いけれど、まあいいわ。はい、お代よ。";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "高いな！そんなに持ってないぜ。また後で話そう。";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "ご希望通りですわ、旦那様。ルシールは夜十一時に心待ちにしておりますの。加えて、 彼女は朝七時より遅く戻ってはなりませんわ。もし真夜中までにいらっしゃらなければ、 彼女は別のお客様の相手をいたしますので、次の晩までお待ちいただくことになりますのよ。それから、決して……彼女を傷つけたりなさいませんように。後悔なさることになりますわよ。ご忠告までに、旦那様。";
			link.l1 = "ご心配なく、恋人のように優しく扱うさ。乱暴なんてしないよ。十一時に彼女をいただこう。さて、 それまで何をしていればいい？";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "そうねえ、わたくしにも分かりませんわ。酒場に立ち寄って、バーテンとお話しになってみてはいかが？";
			link.l1 = "悪くない考えだな。その通りにするぜ。良い一日を！";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

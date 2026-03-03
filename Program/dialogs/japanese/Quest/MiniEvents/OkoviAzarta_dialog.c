void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "何の用だ、 "+GetAddress_Form(NPChar)+"申し訳ないが、新しい注文は受けていないんだ。今は……仕事が多すぎてな。";
			link.l1 = "そうか？最近カードゲームでとても大事な物を失くしたと聞いたが、本当か？";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "さて、もしあんたが俺を嘲笑いに来たんなら、順番を守れよ――あんたがいなくても、そうしたい奴は山ほどいるんだ。だが、誰一人として助けてくれる奴はいなかった。 俺の運命は糸一本でぶら下がっていて、それはすべてハビエル・カスティーリョ次第だ。なのに、 みんな俺の不幸をあざけることしか考えちゃいねえ。";
			link.l1 = "俺は他人の不幸を笑うような奴じゃねえ。どうしてこうなったのか話してみろ。もしかしたら力になれるかもしれねえ。";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "助けてほしいだと？誰がそんなことをしてやるんだ？俺は絶対にしねえよ。自分の幸せも不幸も、自分で鍛えるもんだ……。だから被害者ぶるのはやめろ。自分の行いの結果は当然の報いだ、受け入れろよ。";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "あの晩が命取りになるなんて思ってもみなかった。提督エウヘニオ・デ・ラ・トーレ本人から大量の注文を受けた後、 ラム酒を一杯飲みに酒場へ入っただけだったんだ。しかし、かなり酔っ払ってテーブルに座り、カードを始めてしまった。 そこでハビエルが俺に目をつけたんだ\n最初は運が味方してくれて、そこそこの金も勝った。だが、運を信じ始めた途端、状況は一変した。 ハビエルは俺のマグにラムを注ぎ続け、俺は負け続けた。まず手持ちの金が消え、 次に材料費として取っておいた金も消え、最後には貯金まで全部失った\nどれだけ負けたか気づいた時には、もう引き返せなかった。頭の中は「何としても取り返す」 という思いでいっぱいだった。そして俺は本を賭けてしまった。あの悪党ハビエルは、 たった五千ペソの価値しかないと言いやがった\nもちろん、本当はもっと価値がある。でも興奮で目がくらんで、俺は同意してしまった。そして……その先はもう知ってるだろう。俺は負けた。こんなこと、今まで一度もなかったんだ。あの野郎、 何か薬でも盛ったんじゃないかと思うぜ。";
			link.l1 = "それで、どうやって俺があんたを助けろっていうんだ？自分でテーブルにつき、自分で財産を賭けて、 自分で全部失ったんだろう。今さらその結果を受け入れたくないだけじゃねえか？それに、 その本の何がそんなに大事なんだ、そんなに嘆くほどのもんか？";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "この本は俺が持っていた中で一番貴重なものだ。\n何世代にもわたり師匠から弟子へと受け継がれてきた秘密が書かれている。\nこれは俺の鍛冶場の心臓であり、俺の技の魂だ。\n失ったことはもう受け入れている。 "+GetAddress_Form(NPChar)+"しかし、本を失ったことをどう受け入れればいいんだ？ハビエルに身代金として五千ペソを提示したんだ\n借金してでも取り戻す覚悟だった。でも、あいつがなんて言ったか知ってるか？十万ペソ欲しいって言いやがったんだ！ 十万だぞ、 "+GetAddress_Form(NPChar)+"！そんな大金は持っていません。しかも、あいつは値下げも分割払いも断固として受け付けないんです。 頼み込んだんですが……笑われただけでした。あなたは…… "+GetSexPhrase("勇敢な男、水夫……もしかすると船長かもしれねえ。そして、その武器も飾りじゃなさそうだな","ただの女じゃなく、きっとどんな男にも近づく術を持っているはずだ")+"\nお願いです、ハビエルと話してくれませんか。もしかしたら、あなたの言葉なら彼も耳を貸してくれて、 借金の支払いを延期してくれるかもしれません。この本がなければ……私の人生には意味がありません。その代わり、立ち直ったらいつでも上質な材料をお安くお譲りしますし、 もしかしたら船長のために特別な品も作れるかもしれません。";
			link.l1 = "まあ、話すのは別に面倒じゃねえさ。どうなるかはこれからだな。まずは自己紹介させてもらうぜ。俺の名前は "+GetFullName(pchar)+"、自分の船の船長だ。";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("そして俺はセバスチャン・コルドバだ……","女が――自分の船の船長だと？そんな話は聞いたことがあるが、実際に会ったことも話したこともねえな。")+" お会いできて嬉しいです、船長 "+pchar.lastname+"。ありがとうございます。最近は他人の不幸を笑う奴の方が、助けてくれる人より多いんですよ。\nもし本が戻ってきたら、誓います――もう二度と賭け事なんてしません。";
			link.l1 = "まだ礼を言われるようなことはしていないぜ。まずは自分の用事を片付けてから、時間があればハビエルと話すつもりだ。 ";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "残念ながら、もう遅かったかもしれません。ハビエルは思ったよりもずっと素早かったのです\n彼はすでに本の買い手を見つけてしまいました――フランス人の名高い銃職人、エティエンヌ・ルノワールです。もし提督が、 私のせいでそんな貴重な品がフランス人の手に渡ったと知ったら……首が飛ぶでしょう。牢獄送りなんて、むしろ軽い罰ですよ。";
			link.l1 = "ふむ……よし、すぐにお前の問題を片付けてやる。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Captain "+ pchar.lastname +"「！ハビエルと話したか？何か新しい情報はあるか？」";
			link.l1 = "まだだが、今から酒場に向かうところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "俺は話した"+GetSexPhrase("","")+"。しかも、うまくいったぜ。ハビエルは慌ててこの世を去ったが、その前にお前の本を返してくれた。ほら、これだ。";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"、あなたにはこれが私にとってどれほどの意味を持つか想像もつかないでしょう！あなたのおかげで、 全ての注文をこなせるし、提督の仕事まで果たせるんだ！残念ながら金はないが、それでも報酬を用意したぞ\nほら、このキュイラスを持っていってくれ――あるドンのために作ったものだが、しばらくは待ってもらえるだろう。それと、 自分で何か作る気になった時に役立つ材料もいくつかあるぞ。";
			link.l1 = "ありがとうございます。 "+npchar.name+"、あなたは本当に気前がいいですね！";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "それから、材料が必要ならいつでも寄ってくれ。俺の仕入れは月に一度だから、いつもお前の役に立つ物があるはずだ――しかも安くな。約束は守るぜ。";
			link.l1 = "必ずそうするよ！さて、 "+npchar.name+"、元気でな。俺は行くぜ、やることがあるんだ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Captain "+ pchar.lastname +"「おい！ハビエルと話したか？何か新しい情報はあるか？」";
			link.l1 = "あのな……本は俺の手元にあったんだ。だが……事情があって売られてしまったんだよ。";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "「なにっ！？お前……売ったのか！？俺の本を！？」";
			link.l1 = "お前がカードゲームで失くした本だ。それはハビエルが約束していたあのフランス人に売られたんだ。";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "しかし…もう終わりだ。あの本はフランス人の手に渡ったし、提督の命令も果たせない…俺の人生はおしまいだ…俺は…俺はもうおしまいだ！";
			link.l1 = "自分で自分を追い込んじまったな。これがいい教訓になるだろうぜ。じゃあな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\English\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "「おい、」 "+GetSexPhrase("水夫","かわい子ちゃん")+"、カードで運試ししてみないか？席に座れよ、ここは賭け金も優しいぜ……少なくとも初心者にはな。";
			link.l1 = "俺の探していたのはまさにお前だって気がするぜ。セバスチャンをうまく誘い込んで、骨の髄までしゃぶり尽くしたのも、 まさにこうやったんだろう？\n俺はあいつの本を取り返しに来たんだ。";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "おう、いいぜ。十万くれりゃ持っていっていいぞ。あんな本なんざ俺には用はねえし、 トングとハンマーの区別もつかねえからな。";
			link.l1 = "五千払おう――それはお前が鍛冶屋を打ち負かした時に自分で決めた値段だ。";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "はっ！俺を馬鹿にしてるのか？その本の本当の価値くらい、ちゃんと分かってるぜ。十万だ、一枚たりともまけねえ。 それが嫌ならフランス野郎に売るまでだ――あいつらは金に困っちゃいねえからな。";
			link.l1 = "お前がスペインの設計図をフランスに売っても当局が見て見ぬふりをすると思ってるのか？\n提督がそれを知ったら激怒するぞ。";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "おいおい、そんなこと言うなよ。役人どもは本なんか気にしちゃいねえ、今だって問題山積みだろうが。それに提督か？ あいつはフランス野郎を心底憎んでるが、俺はわざわざ待っててやるつもりはねえ――これだけの金があれば、新世界のどこの植民地でも歓迎される客になれるってもんさ。";
			link.l1 = "それじゃあ、取引しようぜ。金はちゃんと払うが、すぐには無理だ。鍛冶屋が分割で借金を返す。その本は今日、 俺の船長としての名誉を担保に鍛冶屋に戻す。\nお前には何も変わらねえ――奴はちゃんと払うし、お前も一ペソたりとも損はしねえよ。";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "俺の話が聞こえてねえみたいだな。はっきり言ったはずだ――今すぐ金が必要なんだ。一週間後でも、一か月後でも、鍛冶屋がかき集めるまででもなく、今すぐだ。 このみじめな島からできるだけ早く出ていくつもりだからな。だから、今すぐ全額渡すか、 それとも本はフランス人に渡して、お前の船長の名誉は提督の死刑執行人にでも質入れするんだな。";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "こうしようじゃねえか：勝負しようぜ。俺の十万対その本だ。お前が勝てば、この島を大金持ちとして出て行ける。 負けたら――俺がその本をもらう。\nそれとも、デッキを見たこともねえ素人としか勝負しねえのか？";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "はっ！俺は金持ちになる必要なんてねえ――もう十分金持ちだからな！なんでわざわざ大金を手に入れるために危険を冒さなきゃならねえんだ？";
			link.l1 = "ほうほう、ハビエル・カスティーヨ本人が勝負を怖がるとはな？てっきり俺は"+GetSexPhrase(""," あなた")+"、お前はただ酔っぱらいの馬鹿どもから金を巻き上げる悪党じゃなく、百戦錬磨の勝負師だったんだな。";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "怖くなんかねえさ。ただ、もう必要なものは全部持ってるのに、わざわざテーブルに座る意味が見当たらねえだけだ。";
			link.l1 = "おいおい、初めてイカサマなしで勝負する相手にビビって震えてるのが丸わかりだぜ。\n当ててやろうか、そんなに急いでここを出ていきたいのは恥ずかしいからだろ？\nみんなもう、お前が酔っ払いの間抜けより強い相手には勝てないって見抜いてるぜ？";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "よくもそんな口をきけるな！？お前なんぞと同じ卓につくのも嫌がる連中を、俺は叩きのめしてきたんだぜ！ 俺たちが賭けた壺は船が買えるほどで、プレイヤー一人につき傲慢な船長が一人はいたもんさ！さあ、勝負しよう。 カード一枚につき五千、ひとり十万、金が尽きた奴が負けだ。誰が誰を叩きのめすか、見せてもらおうじゃねえか。\n";
			link.l1 = "話はいい、行動だ。取引成立だ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "悪魔め！そんなはずが……";
			link.l1 = "「どうした、他の奴が勝ってるときはあまり面白くねえのか？」";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "てめえ、イカサマしやがったな！俺が何も見てねえと思ったのか？ふざけんな、俺を騙せると思うなよ！てめえなんざ、 ぶった切ってやるぜ。";
			link.l1 = "イカサマだと？ははっ！負け方を知らねえだけじゃねえか、相棒。だが、そんなに死に急ぐなら――俺が手伝ってやるぜ。武器を取れ！";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "はっ！さて、 "+GetSexPhrase("相棒","かわい子ちゃん")+"、身ぐるみ剥がされる気分はどうだ"+GetSexPhrase("","") +"？傲慢は二番目の幸せだと言うが、お前の場合は違うな。";
			link.l1 = "自惚れるなよ。運が良かっただけだ。";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "負け犬はいつもそう言うもんだ。まあ、お前は勝負した\n"+GetSexPhrase("","") +" ―負けたな"+GetSexPhrase("","") +"、気にするなよ。もしまた十万手に入れたら、もう一度運試ししてみな。\nだが、結果は変わらねえと思うぜ……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "「こんにちは」 "+GetAddress_Form(NPChar)+"。どのようなご用件でお越しになったのですか？";
			link.l1 = "ごきげんよう。私は船長だ "+GetFullName(pchar)+"、それとハビエル・カスティーリョについて話したいんだ。";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "ふむ……あの悪党に金を貸してるのはあんただけじゃねえ、長い列に並ぶ覚悟をしな。 ハビエルは借金を返すのに急ぐような奴じゃねえからな。\nだが、もしあいつが金を手に入れたら、まず俺に返すしかないようにしてあるぜ――他に選択肢はねえんだ。";
			link.l1 = "幸い、俺はあいつの債権者じゃねえ。あいつはお前にいくら借りてるんだ？それで、 お前は具体的にどんな手を打ったんだ？";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "彼の借金の総額は十五万ペソだ。支払ったのは一万ペソだけで、それで十分だと思ったらしい。だが、 俺がすぐにそれは間違いだとわからせてやった。俺の手下がさらに二万ペソを回収した。 残りは一週間以内に返さなきゃならねえが、期限はもうすぐだ。幸いなことに、 やつは本を売ってまとまった金を手に入れるらしいと聞いている。";
			link.l1 = "本当にあいつが返してくれると思ってるのか？本気で期待しないほうがいいぜ。ハビエルなんて、 金を手に入れたらすぐにここから逃げるって隠そうともしねえんだぞ。";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "承知していますよ、船長。ご安心ください、すでに奴が支払いを済ませずに逃げられないよう手を打ってあります。";
			link.l1 = "状況はうまく掌握しているようだな。だがな、経験上、用心しすぎて困ることはねえぜ。実は俺、 こういうことの専門家なんだよ。"+GetSexPhrase("","ess")+" 借金の取り立てです。もし私に代理を任せていただければ、あなたのお金を取り戻せます。";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "ああ、船長、この借金を回収するだけでもう俺には大きな負担だ。だからお前の報酬まで払う余裕はねえんだ……";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+"、そのことは心配しなくていいぜ。俺にもこの件には興味があるから、無料で手伝ってやるよ。";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "お聞きしてもよろしいですか、具体的にどのようなご興味がおありなのでしょうか？";
			link.l1 = "まあ、あいつのカードテーブルでのイカサマは、俺が見逃せねえ代物だってことさ。";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "まあ、タダで済むなら断る理由はねえな。ただし一つだけだ、船長――やりすぎないでくれよ。あの野郎が借金を返す前にくたばっちまったら、俺には何の得にもならねえからな。";
			link.l1 = "心配するな、フェリペ、俺が慎重に行動するぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"！まさか、もう片付けたのか？";
			link.l1 = "残念ながら、まだだ。しかし、今取り組んでいる。";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "「ああ、」 "+GetSexPhrase("船長","かわいこちゃん")+" 成り上がり野郎！またお前か？どうした、また何千も失いてえのか？";
			}
			else
			{
				dialog.text = "またお前か？はっきり言っただろう、金を置け――さもなきゃとっとと失せろ。";
			}
			link.l1 = "口の利き方に気をつけろ、ハビエル。それから財布を出せ――俺はタダで来たんじゃねえぞ。フェリペ・アラルコンへの借金、忘れてねえだろうな？今は俺があいつの代理人だ。さあ、 選べ。今すぐ借金を払うか、それともお前がくたばった後でポケットから金を探すかだ。";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "くそっ！今、取引の真っ最中なんだ、見りゃわかるだろうが！あと数時間してから戻ってこい――そしたら話をしてやる。";
			link.l1 = "俺の言ったことが聞こえなかったみたいだな。はっきり言ったはずだ――今すぐ金が必要なんだ。一週間後でも一か月後でも、お前がかき集められるときでもなく、今すぐだ。十二万ペソ、 これっぽっちもまけねえ。本は五千として受け取ってやるぜ。";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("この汚ねえ野郎","この野郎")+"！俺をそんな簡単に片付けられると思ったら、それがお前のくだらねえ人生で一番でかい間違いだぜ。";
			link.l1 = "そのうち分かるさ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "なんて光景だ……認めざるを得ないな。 "+GetAddress_Form(NPChar)+"、あなたには大いに楽しませてもらった。剣の腕前は見事だ。自己紹介させてくれ―― "+GetFullName(npchar)+"。そして、この不運な男は、俺の記憶が正しければ、ハビエル・カスティーリョじゃねえか？";
				link.l1 = "「そう、その男だ。そして俺は船長だ」 "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "なんて光景だ……認めざるを得ないな。 "+GetAddress_Form(NPChar)+"、あなたのおかげで大変愉快な思いをさせてもらった。剣の腕前も見事だな。状況とは不思議なもので、 わざわざ遠くまで探しに来た本が、まさかこんな形で持ち主を変えるとは思わなかったよ。しかし、 ここを手ぶらで去ることにはならないと願いたいものだ。";
				link.l1 = "ふむ……で、この本の価値はいくらだと考えているんだ？";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "ご覧の通り、船長、私はある特別な本のためにかなりの距離を旅してきたんだ……そして今、その本はあなたの手元にあるようだ。心から合意に至れることを願っている――手ぶらでこの地を去るのはご免だからな。";
			link.l1 = "ふむ……で、この本の価値はいくらだと思っているんだ？";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "「ああ、」 "+GetAddress_Form(NPChar)+"、俺は本当に珍しい物の値段を知ってるんだ。八万ペソだぜ。十分すぎるほどの大金だし、信じてくれ、 こんな申し出は二度とないだろうよ。";
			link.l1 = "まあ、その本は確かに貴重だし、正直に言えば俺が頼んだんだ"+GetSexPhrase("","") +" ただの好奇心からだ。俺は人の運命で商売するつもりはねえ。悪いが、旦那、取引はできねえ――この本は本来の持ち主に返さなきゃならねえんだ。";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "笑っちまうような金額だな。この本には鍛冶職人の最高峰たちの秘伝が詰まってるんだぜ。十五万ペソ――払うか、持ち主に返すかだ。値切りはなしだぞ。";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "どうか、そんなに早く断らないでくれ。これのために長い道のりを旅してきたんだ。 あの男を見事に片付けた腕前への敬意として、十万を用意しているんだ、どうだ。";
			link.l1 = "言うべきことは全部言った。\nでは、失礼するぜ。行かなくちゃならねえんだ。";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"、ご信頼には感謝しますが、十五万というのは値段じゃなくて、馬鹿げてますよ。 この取引を茶番にするのはやめましょう。十万ペソが妥当な額です、それで納得してください――この本にそれ以上払う者はいませんよ。";
			link.l1 = "どうやら意見が合わなかったようだな。まあ、この話を続ける理由もないだろう。さらばだ、旦那。";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "待て！わかった、お前の勝ちだ。十五万だ。これで手を打つか？";
			link.l1 = "正しい選択をしてくれて嬉しいぜ。本はお前のものだ。これがあれば、カリブ一の名匠になれると思うぜ。";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"この本がなくても俺は誰にも負けなかったさ。だが、こんな珍しい戦利品を手に入れるのはやはり嬉しいもんだ。さて、 失礼するぜ――噂通りの名品かどうか、早く確かめたくてたまらねえんだ。";
			link.l1 = "それじゃあ、引き止めはしねえ。じゃあな。";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "ほうほう、なんだこのクズは？俺たちの宝箱を空にして逃げようとしたのか？とんだ間抜けだな、野郎。 今度はお前をその箱にぶち込んで、フタを釘で打ち付けてやるぜ！";
			}
			else
			{
				dialog.text = "ほうほう……ここにいるのは誰だ？道に迷ったのかい、お嬢ちゃん？宝箱を空にして、こっそり逃げようと思ったのか？ 大きな間違いだぜ、可愛い子ちゃん。これからしっかり調べさせてもらうぜ――ポケットの中も、他のところもな……。";
			}
			link.l1 = "くだらねえ虫けらどもにゃ、言葉が多すぎるぜ。剣を抜け、お前らの本当の価値を見せてみろ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "船長！ハビエルがあんたのおかげであの世に行ったって、もう聞いてるぜ。しかも、 俺はあいつを早まって殺すなって頼んだはずだ！さて、俺の金を返しに来たんだろうな？";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "その通りだ。奴の隠し場所を見つけて、十万ペソを手に入れた。それが奴の全財産だったんだ。";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "ああ、俺が奴を殺さなきゃならなかったんだ。だが先に襲いかかってきたのは奴の方だ、俺は自分を守るしかなかった。 奴の懐は空っぽで、一文無しだったぜ。残念だが、借金は回収できなかった。";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "十万……もちろん、それが全額じゃないが、ハビエルのことを考えれば、あいつからこれ以上絞り取れる奴はいないだろうな。\nさて、ありがとう、船長。どうやら私は人選を間違えたようだ。あなたこそ本物のプロだな。";
			link.l1 = "難しくはなかった。さて、それでは失礼させていただきます"+GetSexPhrase("","")+"。仕事が待っている。";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "さらばだ、船長。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "You "+GetSexPhrase("ろくでなし","ろくでなし")+"俺の目を見ながら平気で嘘をつきやがって！？このまま逃がすと思うなよ！";
			link.l1 = "「アルッ…」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			dialog.text = "「こんにちは」 "+pchar.name+"！資材か商品をお求めですか？";
			link.l1 = ""+TimeGreeting()+"。何を持っているか見せてくれ。";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "「そして、君にも挨拶を」 "+npchar.name+"！申し出はありがたいが、俺はただ"+GetSexPhrase("","") +" 挨拶するためだ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"、結局何かお買い求めになるご決心をされたのですか？";
			link.l1 = "その通りだ。今日は何を持っているか見せてくれ。";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "悪いが、もう行くぜ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}
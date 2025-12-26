//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("「この町はあんたのものだって噂だぜ」 "+GetSexPhrase("旦那","お嬢さん")+".","「なんて愉快な出会いだ」 "+GetSexPhrase("旦那","お嬢さん")+"!");
					link.l1 = RandPhraseSimple("気が変わった。幸運を祈るぜ！","町をぶらぶらしているだけさ。じゃあな。");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","情報が必要だ。");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("財政のことについて話したい。","「財政について…」");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("警報だ！武装した狂人がいるぞ！武器を取れ！","武器を持った狂人がいるぞ！武器を取れ！");
						link.l1 = RandPhraseSimple("「何だって！？」","何をしているんだ！？");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("何の用だ？さっさと行け。","俺の行く手を邪魔するな、どけ。");
						link.l1 = RandPhraseSimple("なあ、分かってるか？吠えるんじゃねえ！","落ち着け。さもないと俺がやるぞ！");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("あなたに聞きたいことがある。","少しお時間をいただけますか。\n一つだけ質問があります。");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("財政のことについて話したい。","財政について……");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。あなたが自分の船の船長だと見受けます。お願いしたいことがあるのですが…";
					link.l1 = "「聞いているぞ」 "+GetAddress_FormToNPC(NPChar)+"……何の用だ？";
					link.l1.go = "passenger";
					link.l2 = "申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"、しかし急いでいるんだ。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("私は ","私の名前は ","俺をこう呼んでくれ ")+GetFullName(npchar)+LinkRandPhrase("……何の用だ？","。お前を見るのは初めてだな。誰だ？","。お前は誰だ、俺に何の用だ？"),LinkRandPhrase("「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。私の名前は "+GetFullName(npchar)+"。ところで、お前の名前は何だ？","「こんにちは。」 "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(npchar)+"。お名前をお聞きしてもよろしいですか？","「はい。」 "+GetAddress_Form(NPChar)+"。何の用だ？ところで、俺の名前は "+GetFullName(npchar)+"。ところで、お前の名前は何だ？"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("くそったれ！ ","くそっ！ ","くたばりやがれ！ ")+"ああ、俺が船長だ "+GetFullName(Pchar)+LinkRandPhrase("、聞いたことがないのか "+NPCharSexPhrase(NPChar,"、この野郎か？","?")," そして "+GetSexPhrase("一番有名な海賊","最も有名な女海賊")+" 海の上だ！"," もし俺が間違ってたら、くたばってもいいぜ！"),LinkRandPhrase("私は "+GetFullName(Pchar)+"「船長。」","私の名は "+GetFullName(Pchar)+".","俺のことは船長と呼んでくれ "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("街中が緊張している――王室監察官のドン・フェルナンド・デ・アラミダが到着したんだ。\nここでいろいろ見てきたが、これは……人を変えるのは悲しみそのものじゃなく、それにどう向き合うかなんだよ。\n彼は父親の死後、別人になったと言われている。今じゃ、群島中でこれほど清廉潔白で……そして容赦ない王冠の僕は他にいないさ。","『ホーリー・マーシー』を見てみろよ！王様自ら特別な設計で造らせたって話だぜ。しかも見ろよ、傷一つねえ。 まるで聖母マリア様が守ってるみてえだ。だが噂も聞いたぜ……もしかすると聖母じゃねえかもしれねえってな。","ドン・フェルナンドが何度も命を狙われたのをご存知か？公開海域で十二回も襲撃されたんだぞ――しかもそれは去年だけでだ！\nだが、あれほど忠実で鍛え上げられた乗組員がいて、さらに主のご加護もある。十三回目もきっと生き延びるさ！"),LinkRandPhrase("聞いたか？ドン・フェルナンド・デ・アラミダがうちの街に来たらしいぜ、今まさにどこかの通りにいるって話だ。 自分の目で一度見てみたいもんだな…","複雑な男だよ、このドン・フェルナンドは。母国の汚れを清める救世主だと言う者もいれば、 父親の死で彼の中の何かが壊れ、やがて俺たち全員が泣くことになると囁く者もいる。\nだが俺が言いたいのはこれだ――彼を恐れるな。彼をこうした連中を恐れろ。","なんてハンサムな男なの、あのドン・フェルナンド！でもね、不思議なのよ。まるで誰にも気づいていないみたい。 すべてが義務と奉仕なの。女の子がいたって聞いたけど……ある神父と会ってから、俗世の楽しみを完全に断ったのよ。まるで誓いを立てたみたいに。"),RandPhraseSimple(RandPhraseSimple("くそったれ検査官め！あいつがいる間は、町がまるで死んだようだ。商売もできねえし、楽しみもねえ。 息をするのさえ静かにしなきゃならねえみたいだぜ。\nそして一番怖いのはな、どこの港でも同じなんだ。まるで機械仕掛けみてえによ。 王様がわざと俺たち全員にこの拷問を考えついたんじゃねえかって思うぜ！","ドン・フェルナンドがまた孤児院を訪れたんだ。惜しみなく寄付し、何時間も祈っている。あんな立派な男こそ、あの忌々 しい横領者どもへの手本にすべきだ！"),RandPhraseSimple("はっ！「聖人」フェルナンドがまた娼館を全部閉めちまったぜ。まあいいさ、あいつもすぐに出航するだろうし、 そしたらまたすぐ開くだろうよ。","検…検査官が来たんだよ、それが何だってんだ！ドン・フェルナンド・デ・アルメイダ、いや、名前は何だったか、 アラミーダとか！あまりにも偉い奴だから、総督ですら奴の前じゃ腫れ物に触るような態度だってさ。 目を覗き込まれたら、一瞬で全部の罪を見抜かれるって噂だ。怖いぜ！")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("俺はちょっと、この「町」とやらの穴について聞きたいだけだぜ。","この町についてちょっと聞きたいことがあるんだ。");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","俺はちょっと情報が必要だ。");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("財政のことについて話したい。","「財政について…」");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "聞いてくれ、助けてほしいんだ。俺は買いたいものがあるんだが "+pchar.GenQuest.Device.Shipyarder.Type+"、それでこの品があんたの町で売られてたって聞いたんだ。まあ、誰かが通りで売ってたらしい。何か知ってるか？";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("知っているか ","ご存知か ","聞いたことがあるか ")+" 最近この地元の教会が盗まれたってことか？";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("ああ、お前か "+GetFullName(Pchar)+" "+GetSexPhrase("- 古い友よ！","- きれいなお嬢ちゃん！")+"","お会いできて嬉しいです。 "+GetSexPhrase("古い友よ！","「可愛い子ちゃん！」")+" "+Pchar.name,"「ああ、それが」 "+GetSexPhrase("船長本人","船長本人")+" "+GetFullName(Pchar))+RandPhraseSimple("。お前は死んだと思ってたぞ！","。そして、もしかすると "+GetSexPhrase("いつも通り酔っ払ってるな。","少し酔っている。"))+LinkRandPhrase(" 続けてくれ、何が必要なんだ？"," 今度は何だ？"," また俺にちょっかいかけるのか？"),LinkRandPhrase(TimeGreeting()+"「船長」 ","「ごきげんよう。」 "+GetAddress_Form(NPChar)+" ","ごきげんよう、船長 ")+GetFullName(Pchar)+LinkRandPhrase("。どうなさいましたか "+GetSexPhrase("「そんな立派な男」","「なんて立派な娘だ」")+"、お前のような奴か？","。なぜここにいるんだ？","。今度は何を知りたいんだ？")),PCharRepPhrase(LinkRandPhrase("やあ、船長 ","ごきげんよう、ああ、あなただったか "+GetAddress_Form(NPChar)+" ","ああ、船長 ")+GetFullName(Pchar)+LinkRandPhrase("、もう二度と会えないと思っていた、そして","、会えて嬉しいとは言わねえが","、まだ生きているとはな、残念だぜ、そして")+LinkRandPhrase(" 何の用だ？"," なんでここにいるんだ？"," どうされましたか？お力になれることはありますか？"),LinkRandPhrase(TimeGreeting()+"、船長 "+GetFullName(Pchar)+"。どうなさいましたか？","ああ、あれが船長だ "+GetFullName(Pchar)+"！どうなさいましたか？","「ごきげんよう。」 "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"。何か用か？")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもないさ、ちょうど酒場に向かうところだったんだ。"),RandPhraseSimple("ああ、もういいさ。幸運を祈るぜ！","街をぶらぶらしていただけさ。では、さらば。"));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "質問はあるか？";
			link.l1 = "この書類に書かれている名前に心当たりはあるか？";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("俺はそんな紙切れなんざ気にしねえし、そもそも字なんか読めねえんだ。高利貸しのところに行けよ、 あいつは手紙の扱い方を知ってるってさ、ははっ！","何のことか分からねえ、他の奴に聞いてくれ、船長"+GetFullName(Pchar)+".","どう助ければいいのかわかりません、船長 "+GetFullName(Pchar)+" 金貸しに話してみろ、何か知ってるかもしれねえぞ。");
			link.l1 = "ありがとう。";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("嘘ついてないか、船長 "+GetFullName(Pchar)+"?","だから何だ "+PChar.name+"?","「あなたのことは忘れない」 "+GetFullName(Pchar)+".")+" さあ、何が望みだ？",LinkRandPhrase("お会いできて光栄です、船長 "+PChar.name,"会えて嬉しいよ。 "+GetAddress_Form(NPChar)+" "+PChar.lastname,"お会いできて光栄です、船長 "+PChar.name)+"。しかし、俺の名前だけを知りたかったわけじゃねえだろ？");
            link.l1 = PCharRepPhrase("俺はただ、このクソみたいな“町”についてちょっと聞きたいだけだぜ。","この町についてちょっと聞きたいことがあるんだ。");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","ちょっと情報が必要なんだ。");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("財政の件について話したい。","「財政について…」");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "聞いてくれ、助けてほしいんだ。俺は買いたいものがあるんだが "+pchar.GenQuest.Device.Shipyarder.Type+"、それでこの品があんたの町で売られていたと聞いたんだ。まあ、誰かが通りで売っていたらしい。何か知ってるか？";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("知っているか ","ご存知ですか ","聞いたことがあるか ")+" 最近この地元の教会が盗まれたってことか？";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもないさ、ちょうど酒場へ向かうところだったんだ。"),RandPhraseSimple("まあ、なんでもねえさ。幸運を祈るぜ！","街をぶらぶらしていただけさ。じゃあな。"));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("ああ、それにお前に会えて酒を飲むのと同じくらい嬉しいぜ。何でも聞いてくれ。","話すのが好きかい、船長？俺もさ……特にラム酒を一杯やりながらな。","「はい」 "+PChar.name+"?"),LinkRandPhrase("他に何の用だ？","いただくぜ、船長 "+PChar.name+"「お前はおしゃべりが好きなんだな？」")),PCharRepPhrase(LinkRandPhrase("他に何が欲しいんだ、 "+GetAddress_Form(NPChar)+"?","聞いているぞ、船長。","俺は行かなきゃならねえんだ、だから早く用件を言ってくれ、船長。"),LinkRandPhrase("「楽しい仲間がいるのはいつでも嬉しいぜ」 "+GetAddress_Form(NPChar)+" "+PChar.lastname+"「……話せ。」","「はい。」 "+GetAddress_Form(NPChar)+"?","話すのが好きかい、船長？俺もさ…… ")));
			link.l1 = LinkRandPhrase("この町でどんな噂が流れているんだ？","この辺りで何か新しい噂はあるか？","陸での暮らしはどうだ？");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("道を教えてくれるか？","「ある場所への道が見つからねえんだ……」","「ある場所まで連れて行ってくれ……」");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("人々がある人物について何と言っているのか知りたいんだ。","誰かについて人々が何と言っているか知っているか？");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("地元の人々についてもっと知りたいんだ。","地元の連中について何か知ってるか？");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもない。今から酒場に向かうところだ。"),RandPhraseSimple("まあ、なんでもねえさ。幸運を祈るぜ！","町をぶらぶらしていただけさ。じゃあな。"));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "誰に興味があるんだ？";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "総督についてもっと知りたいんだ。";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "地元の酒場の主人についてもっと知りたいんだ。";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "地元の造船所の親方についてもっと知りたいんだ。";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "地元の店主についてもっと知りたい。";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "たいしたことじゃねえ。気にすんな。";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "ありがとう。";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "「ふむ、」 "+pchar.GenQuest.Device.Shipyarder.Type+"？聞いたことがねえな……俺はここに長く住んでるが、そんなもん見たこともねえよ。";
			link.l1 = "「まあ、それは造船用の道具だな。」 "+pchar.GenQuest.Device.Shipyarder.Describe+"。町でそんなものを売っている者はいなかったか？あるいは持ち歩いているのを見かけたことは？";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "ふむ……ああ、数時間前にその品を持った男を見かけたぜ。通りを歩いていたよ。面白い道具だったな。";
				link.l1 = "どんな奴だったんだ？それに、どこへ向かっていた？そういう情報が本当に必要なんだ。";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いや、そんなものは見てないぜ。";
				link.l1 = "なるほど。じゃあ、これからも聞き続けるぜ。";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("いいや、そのことについては何も知らねえ。","いや、俺が行くべきだ。","俺は何も知らねえ。");
					link.l1 = LinkRandPhrase("「結構です、ありがとう。」","なるほど、ありがとうございます。","わかった、失礼する。");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("そのことについては何も知らねえが、酒場の常連に聞いてみな。きっともっと教えてくれるぜ。","何も話せねえ、酒場で誰かに聞いてくれ。");
				link.l1 = "助かったぜ。";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "船長、俺は「」という名の植民地に行く必要がある "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+"、できるだけ早く、それが始まる "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+"、で "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+"。お前の船は、ここを航行している小舟どもと比べりゃ、ずいぶん頑丈そうだな。俺はお前に支払いができるぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+"。どう思う？";
			}
			else
			{
				dialog.text = "船長、植民地まで連れて行ってほしい "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+"、それは "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"、ある "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+"。これは非常に危険に聞こえるのは分かっているが、もしかすると\n "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" お前にとっていい後押しになるんじゃねえか？";
			}
			link.l1 = "ふむ。俺もこの道を行くところだ、だからこの条件でお前を乗せてやるぜ。";
			link.l1.go = "passenger_1";
			link.l2 = "申し訳ない  "+GetAddress_FormToNPC(NPChar)+"、だが俺は別の方向へ航海しているんだ。手助けはできねえ。";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "残念だな。まあ、別の船を待つとするか。じゃあな。";
			link.l1 = "じゃあな。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "よし、待つのはもううんざりだ。着いたら報酬を渡すからな。";
			link.l1 = "俺の船に行け。 "+GetAddress_FormToNPC(NPChar)+"。もうすぐ出発するぞ。";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "着きましたね、素晴らしい！あなたの船での旅はとても快適でした。感謝します。お金を受け取ってください、旦那。";
			link.l1 = "「幸運を祈る」 "+GetAddress_FormToNPC(NPChar)+"！さらばだ。";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、この町の市民として、剣を納めてくれ。","聞いてくれ、この町の市民として頼む、剣を納めてくれ。");
				link.l1 = LinkRandPhrase("「よし。」","ご希望の通りに。","おっしゃる通りで……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"武器を持って走るのは気をつけてくれ。俺は落ち着かなくなるんだ……","俺の前を見知らぬ奴が抜き身の剣を持って歩いてるのは気に入らねえな……");
				link.l1 = RandPhraseSimple("分かった。","心配するな。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}

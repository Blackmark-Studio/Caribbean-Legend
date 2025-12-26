//Jason общий диалог мещанок
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
    string sTemp, sCity;
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
				    dialog.text = RandPhraseSimple("「この町はあんたのものだって聞いたぜ」 "+GetSexPhrase("旦那","お嬢さん")+".","なんて嬉しい出会いだ！なんて嬉しい出会いだ！総督ご本人が私と話してくださっている！");
					link.l1 = RandPhraseSimple("気が変わった。幸運を祈るぜ！","町をぶらついていただけだ。じゃあな。");
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
				    dialog.text = RandPhraseSimple("何の用だ？さっさと行け。","俺の行く手を邪魔するな、消え失せろ。");
					link.l1 = RandPhraseSimple("何をしているんだ？","落ち着け。さもないと俺が黙らせてやるぜ。");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("あなたに聞きたいことがある。","少しお時間をいただけますか。\n一つだけ質問があります。");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("財政のことについて話したい。","「財政について……」");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("私は","私の名前は ","俺のことは、こう呼んでくれていいぜ ")+GetFullName(npchar)+LinkRandPhrase("……何の用だ？","。お前を見るのは初めてだ "+"「お前は誰だ？」","。お前は誰だ、俺に何の用だ？"),LinkRandPhrase("「ごきげんよう」 "+GetAddress_Form(NPChar)+"。私の名前は "+GetFullName(npchar)+"。ところで、お前の名前は何だ？","Hello "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(npchar)+"。お名前を伺ってもよろしいですか？","「はい」 "+GetAddress_Form(NPChar)+"。何の用だ？それと、ちなみに俺の名前は "+GetFullName(npchar)+"。で、名前は何だ？"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("ちくしょう！ ","くそっ！ ","くたばりやがれ！ ")+"ああ、俺が船長だ "+GetFullName(Pchar)+LinkRandPhrase("「俺のこと、聞いたことねえのか、この野郎？」"," そして "+GetSexPhrase("最も有名な海賊","「最も有名な女海賊」")+" 海の上だ！"," もし俺が間違ってたら、くたばってもいいぜ！"),LinkRandPhrase("私は "+GetFullName(Pchar)+"、船長。","私の名前は "+GetFullName(Pchar)+".","俺のことは船長と呼んでくれ "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("街中が緊張している――王室監察官のドン・フェルナンド・デ・アラミダが到着したんだ。\nここでいろいろ見てきたが、これはな……人を変えるのは悲しみそのものじゃなく、それにどう向き合うかだと言う。\n彼は父親の死後、まるで別人になったらしい。今じゃ群島中どこを探しても、あれほど清廉で……そして容赦ない王冠の下僕はいないさ。","『ホーリー・マーシー』を見てみろよ！王様自ら特別な設計で造らせたって話だぜ。しかも見てみろ、傷一つねえ。 まるで聖母マリア様が守ってるみてえだ。\nだが噂も聞いたことがある……もしかしたら、聖母じゃねえかもしれねえってな。","ドン・フェルナンドが殺されかけた回数を知ってるか？公海で十二回も襲撃されたんだぞ――しかもそれは去年だけでだ！\nだが、あれほど忠実で鍛えられた乗組員がいて、主のご加護もある。十三回目もきっと生き延びるさ！"),LinkRandPhrase("聞いたかい？ドン・フェルナンド・デ・アラミダがうちの町に来たんだってさ、今まさにどこかの通りにいるらしいよ。 自分の目で一度見てみたいもんだな……","複雑な男だよ、このドン・フェルナンドは。母国を汚れから清める救世主だと言う者もいる。だが、 父親の死で何かが壊れ、やがて我々全員が泣くことになると囁く者もいる。\nだが俺が言いたいのはこれだ――彼を恐れるな。彼をこうした連中こそ恐れるべきだ。","なんてハンサムな男なの、あのドン・フェルナンド！でもね、不思議なのよ。まるで誰のことも目に入らないみたい。 義務と奉仕ばかり。女の子がいたって噂も聞いたけど……ある神父と会ってからは、すっかり俗世の楽しみを拒んじゃったの。まるで誓いを立てたみたいに。"),RandPhraseSimple(RandPhraseSimple("くそったれ検査官め！あいつがいる間は町が死んじまう。商売も遊びもできねえ。 息をするのさえ静かにしなきゃならねえみたいだ。\nそして一番怖いのはな、どの港でも同じなんだぜ。まるで機械仕掛けみてえによ。王様が俺たち全員を苦しめるために、 わざとこんな拷問を考え出したんじゃねえかって思うくらいだ！","ドン・フェルナンドはまた孤児院を訪れました。彼は惜しみなく寄付し、何時間も祈りを捧げています。 かくも立派な方こそ、あの呪われた横領者どもへの手本とすべきです！"),RandPhraseSimple("はっ！「聖人」フェルナンドがまた娼館を全部閉めやがった。まあ、気にすんな、あいつもすぐに出航するだろうし、 そしたらまたすぐに開くだろうぜ。","検…検査官が来たんだよ、それが何だってんだ！ドン・フェルナンド・デ・アルメイダ、いや、なんて名前だったか、 アラミダとか！あまりにも偉いから、総督ですら腫れ物に触るような扱いだってさ。 奴は目を見ただけでお前の罪を全部見抜くらしいぜ。怖ぇよな！")));
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
				link.l1 = "この町についてちょっと話したかったんだ。";
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","情報が必要だ。");
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
						link.l3 = RandPhraseSimple("財政のことについて話したい。","「財政について……」");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "聞いてくれ、助けてほしいんだ。俺は買いたいものがあるんだが "+pchar.GenQuest.Device.Shipyarder.Type+"、それでこの品があなたの町で売られていたと聞いたんだ。まあ、誰かが露店で売っていたらしい。何か知ってるか？";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("知っているか ","ご存知ですか ","聞いたことがあるか ")+"最近この地元の教会が盗まれたってことか？");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("ああ、お前か "+GetFullName(Pchar)+" "+GetSexPhrase("- 古い友よ！","- きれいなお嬢ちゃん！")+"","会えて嬉しいよ。 "+GetSexPhrase("「古い友よ！」","かわいこちゃん！")+" "+Pchar.name,"「ああ、それが」 "+GetSexPhrase("船長本人","船長本人")+" "+GetFullName(Pchar))+RandPhraseSimple("。お前は死んだと思ってたぞ！","。もしかすると "+GetSexPhrase("いつも通り酔っ払ってるな。","少し酔っている。"))+LinkRandPhrase(" 続けてくれ、何が必要なんだ？"," 今度は何だ？"," また俺にちょっかい出すのか？"),LinkRandPhrase(TimeGreeting()+"、船長 ","ごきげんよう。 "+GetAddress_Form(NPChar)+" ","ごきげんよう、船長 ")+GetFullName(Pchar)+LinkRandPhrase("。どうなさいましたか "+GetSexPhrase("「そんな立派な男」","「そんな立派な娘」")+"、お前のような奴か？","。なぜここにいるんだ？","。今度は何を知りたいんだ？")),PCharRepPhrase(LinkRandPhrase("やあ、船長 ","ごきげんよう、ああ、君か "+GetAddress_Form(NPChar)+" ","ああ、船長 ")+GetFullName(Pchar)+LinkRandPhrase("、もう二度と会えないと思っていた、そして","、会えて嬉しいとは言わねえが","、まだ生きているとはな、残念だし")+LinkRandPhrase(" 何の用だ？"," なんでここにいるんだ？"," どうされましたか？お手伝いできることはありますか？"),LinkRandPhrase(TimeGreeting()+"、船長 "+GetFullName(Pchar)+"。どうなさいましたか？","ああ、あれが船長だ "+GetFullName(Pchar)+"「！どうなさいましたか？」","「ごきげんよう」 "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"。何かご用ですか？")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもない、ちょうど酒場へ向かうところだったんだ。"),RandPhraseSimple("わかったよ、どうでもいいさ。幸運を祈るぜ！","街をぶらぶらしていただけさ。じゃあな。"));
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
			dialog.text = LinkRandPhrase("俺はそんな得体の知れねえ紙なんざ気にしねえし、字も読めねえんだ。高利貸しのところへ行けよ、 あいつはあの悪魔の文字が読めるらしいぜ。","何のことを言っているのかわかりません、他の町の住民に聞いてください、船長。"+GetFullName(Pchar)+".","俺にはどう助ければいいのか分からねえよ、船長 "+GetFullName(Pchar)+" 金貸しに話してみろ、何か知ってるかもしれねえ。");
			link.l1 = "喜んであなたの助言に従います！";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("嘘ついてるんじゃねえか、船長 "+GetFullName(Pchar)+"?","だから何だ"+PChar.name+"?","「あなたのことは忘れない」 "+GetFullName(Pchar)+".")+" さあ、何が望みだ？",LinkRandPhrase("はじめまして、船長 "+PChar.name,"「お会いできて嬉しいです」"+GetAddress_Form(NPChar)+" "+PChar.lastname,"お会いできて光栄です、船長 "+PChar.name)+"。しかし、俺の名前だけを知りたかったわけじゃねえだろ？");
            link.l1 = PCharRepPhrase("俺はちょっと、この「町」とやらの穴について聞きたいだけだぜ。","この町についてちょっと聞きたいことがあるんだ。");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","情報が必要だ。");
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
					link.l3 = RandPhraseSimple("財政のことについて話したい。","「財政について…」");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "聞いてくれ、助けてほしいんだ。俺は買いたいものがあるんだが "+pchar.GenQuest.Device.Shipyarder.Type+" それで、この品があんたの町で売られていたと聞いたんだ。\nまあ、誰かが通りで売っていたらしい。何か知ってるか？";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("知っているか ","ご存知か ","聞いたことがあるか ")+" 最近この地元の教会が盗まれたってことか？");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもないさ、ちょうど酒場に向かうところだったんだ。"),RandPhraseSimple("まあ、なんでもねえさ。幸運を祈るぜ！","街をぶらぶらしていただけだ。じゃあな。"));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("ああ、それに君に会えて酒を飲むのと同じくらい嬉しいぜ。何でも聞いてくれ。","話すのが好きかい、船長？俺もさ……特にラム酒を一杯やりながらな。","「はい。」 "+PChar.name+"?"),RandPhraseSimple("他に何が欲しいんだ？","いただくぜ、船長 "+PChar.name+"、おしゃべりを楽しんでいるのか？")),PCharRepPhrase(LinkRandPhrase("他に何が欲しいんだ "+GetAddress_Form(NPChar)+"?","聞いているぞ、船長。","俺は行かなくちゃならねえ、だから早く聞いてくれよ、船長。"),LinkRandPhrase("「楽しい仲間がいるのはいつだって嬉しいぜ」 "+GetAddress_Form(NPChar)+" "+PChar.lastname+"「……話せ。」","「はい」 "+GetAddress_Form(NPChar)+"?","話すのが好きかい、船長？俺もさ…… ")));
			link.l1 = LinkRandPhrase("この町でどんな噂が流れているんだ？","この辺りで何か新しい話はあるか？","陸での暮らしはどうだ？");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("道を教えてくれるか？","俺はある場所への道が見つからねえんだ……","「ある場所まで連れて行ってくれ……」");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("人々がその人物について何と言っているのか知りたい。","人々がある人物について何と言っているか知っているか？");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("地元の人々についてもっと知りたいんだ。","地元の連中について何か知ってるか？");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("耳を疑っているようだな。俺は行かなくちゃならねえ。","いや、なんでもないさ、ちょうど酒場に向かうところだったんだ。"),RandPhraseSimple("まあ、なんでもねえさ。幸運を祈るぜ！","町をぶらついているだけだ。じゃあな。"));
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
				link.l2 = "地元の酒場の主人についてもっと知りたい。";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "地元の造船所の親方についてもっと知りたい。";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "地元の店主についてもっと知りたいんだ。";
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
           dialog.text = "ふむ、 "+pchar.GenQuest.Device.Shipyarder.Type+"？聞いたことがねえな……俺はここに長く住んでるが、そんなもの見たこともねえよ。";
			link.l1 = "「ふむ、それは造船用の道具だ。」 "+pchar.GenQuest.Device.Shipyarder.Describe+"町でそんなものを売っている奴を見かけたことはあるか？それとも、持ち歩いているのを見たことがあるか？";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "ふむ……ああ、数時間前にその物を持った男を見かけたよ。街を歩いていたんだ。面白い道具だったな。";
				link.l1 = "どんな顔をしていて、どこへ向かっていたんだ？そういう情報が本当に必要なんだ。";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いいや、そんなものは見てねえな。";
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
				dialog.text = RandPhraseSimple("そのことは何も知らねえが、酒場の常連に聞いてみたらどうだ、きっともっと詳しく教えてくれるぜ。","俺には何も話せねえ、酒場の誰かに聞いてくれ。");
				link.l1 = "助かったぜ。";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、この町の市民として、剣を納めてくれ。","聞いてくれ、この町の市民として、君に剣を納めてほしいんだ。");
				link.l1 = LinkRandPhrase("「よし。」","ご希望の通りに。","おっしゃる通りだ……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"武器を持って走るのは気をつけてくれ。俺は落ち着かなくなるんだ……","見知らぬ男が抜き身の武器を持って俺の前を歩くのは気に入らねえ。怖いんだよ……");
				link.l1 = RandPhraseSimple("分かった。","心配するな。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}

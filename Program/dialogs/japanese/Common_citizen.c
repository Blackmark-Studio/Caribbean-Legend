// boal 25/04/04 общий диалог горожан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
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
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("「間者か？衛兵！」","警報だ！侵入者がいるぞ！");
				link.l1 = "黙れ。俺は行くぞ。";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("「この町を仕切っているのはあんただって話だが、」 "+GetSexPhrase("旦那","お嬢さん")+".","なんと嬉しい出会いだ、市長が私に質問を持って近づいてきた。");
					link.l1 = RandPhraseSimple("気が変わった。","俺はただこの町を探索しているだけだ。じゃあな。");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("お前に聞きたいことがあるんだ。","情報が必要だ。");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("商談について話したい。","「財政についてですが…」");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("何の用だ？さっさと行け。","邪魔するな、どけ！");
					link.l1 = RandPhraseSimple("おい、うるさく吠えるのはやめろよ、いいか？","落ち着け、さもないと後悔するぜ！");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("お前に聞きたいことがある。","少しお時間をいただけますか。質問があります。");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("商談について話したい。","「財政について…」");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("私の名前は ","私の名前は ","俺をこう呼んでくれていいぜ ")+GetFullName(npchar)+LinkRandPhrase("。何の用だ？","。まだだ "+NPCharSexPhrase(NPChar,"ここであんたを見たことがあるぜ","前にそこでお前を見たことがある")+"「お前は誰だ？」","。お前は誰だ、俺に何の用だ？"),LinkRandPhrase("「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。私の名前は "+GetFullName(npchar)+"。君の名前は？","「こんにちは」 "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(npchar)+"。お名前を伺ってもよろしいですか？","「はい」 "+GetAddress_Form(NPChar)+"。何の用だ？ところで、私の名前は "+GetFullName(npchar)+"。で、お前は誰だ？"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("「なんてこった！」 ","地獄の鐘が鳴るぜ！ ","「くたばりやがれ！」 ")+"ああ、俺が船長だ "+GetFullName(Pchar)+LinkRandPhrase("、本当に俺のことを聞いたことがないのか"+NPCharSexPhrase(NPChar,"、野郎か？","?")," そして "+GetSexPhrase("「最も悪名高い海賊」","「最も悪名高い女海賊」")+" この海域で！ "," それが嘘なら地獄で焼かれてもかまわねえ！"),LinkRandPhrase("俺が船長だ"+GetFullName(Pchar)+".","私の名前は "+GetFullName(Pchar)+".","俺のことは船長と呼んでくれていいぜ "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "船長、どうか助けていただけませんか？";
					link.l1 = LinkRandPhrase("すまないが、無理だ。俺にはあまり時間がないんだ。","悪いが、無理だ。忙しすぎるんだ。","いいえ、できません。私には急ぎの用事がありますので。");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("ああ、できるぜ。何か問題でもあるのか？","ああ、手を貸してやるよ。お前のその仕事についてもっと詳しく話してくれ。","お前の商売についてもっと詳しく聞かせてくれ……");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "はい、船長、聞いております。";
					link.l1 = NPChar.name+"、あなたの結婚指輪を見つけた。";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("この町についてもっと知りたいんだ。","この町について教えてくれ。");
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
						link.l3 = RandPhraseSimple("商談について話したい。","「財政について……」");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("待て！今すぐお前が何者か教えろ！私は総督の依頼で敵のスパイを探しているんだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","止まれ！俺はこの町の利益のために行動しているんだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 総督の命令で来た。敵の工作員をこの街で捜索している。","止まれ、友よ！ここの総督が "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 町でスパイを見つけたいと思っている。"),LinkRandPhrase("待て、姐さん！今すぐ自分が何者か言え！俺は総督の依頼で敵の間者を探しているんだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","女、君を拘束しなければならん！町の利益のために行動しているのだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 総督の命令で来た。敵の密偵をこの街で捜索している","じっとしていろ、美人！地元の総督が "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 町でスパイを見つけたがっている…"));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "何かアドバイスをもらえないか。購入したいんだ "+pchar.GenQuest.Device.Shipyarder.Type+"、それがあなたの町で売られていると聞いたんだ。まあ、誰かが通りで売っていたらしい。何か知ってるか？";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("ご存知ですか","知っていたか","聞いたか")+" 最近この地元の教会が襲撃されたってことか？");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("「ああ、お前か。」 "+GetFullName(Pchar)+" "+GetSexPhrase("、この老いぼれ悪党め","- イケてる女")+"","また会えて嬉しいよ、 "+GetSexPhrase("旦那","美しさ")+" "+Pchar.name,"おお、懐かしい "+GetSexPhrase("Captain","ご婦人")+" "+GetFullName(Pchar))+LinkRandPhrase("。お前は死んだと思ってたぞ！","。そしてきっと、 "+GetSexPhrase("いつも通り酔っ払ってるな。","すでに体調が悪いんだ。")+"","。しかも、まだ自由の身のようだな！")+LinkRandPhrase(" さあ、言いたいことを言え――何が必要なんだ？"," 今度は何の用だ？"," またくだらねえことで俺にちょっかい出してるのか？"),LinkRandPhrase(TimeGreeting()+"「、船長」 ","「こんにちは」 "+GetAddress_Form(NPChar)+" ","ご挨拶申し上げます、船長 ")+GetFullName(Pchar)+LinkRandPhrase("。何が "+GetSexPhrase("なんて勇敢な紳士なんだ","「なんて華やかなご婦人だ」")+"、そうかい？俺に何か必要なものでもあるのか？","。何の用でここに来たんだ？","。今回は何を知りたいんだ？")),PCharRepPhrase(LinkRandPhrase("やあ、船長 ","こんにちは。ああ、お前か "+GetAddress_Form(NPChar)+" ","「ああ、船長」 ")+GetFullName(Pchar)+LinkRandPhrase("、と思った"+NPCharSexPhrase(NPChar," "," ")+"「もう二度と会うことはないだろう」","、嬉しいとは言えねえな"+NPCharSexPhrase(NPChar," "," ")+"あなたに会えて、でも","、なるほど、まだ生きてやがるのか。残念だぜ。さて、")+LinkRandPhrase(" 何の用だ？"," 何の用で来たんだ？"," 俺に何ができる "+NPCharSexPhrase(NPChar,"お手伝いできることは？","お手伝いできることは？")),LinkRandPhrase(TimeGreeting()+"「、船長」 "+GetFullName(Pchar)+"。何かご用ですか？","おや、これは"+GetSexPhrase("","")+" Captain "+GetFullName(Pchar)+"！今回は何を知りたいんだ？","「こんにちは」 "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"。何か用か？")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("いや、空耳だぜ。もう行くぞ。","いや、何でもない――ちょうど向かうところだった"+GetSexPhrase("","")+" 酒場へ。"),RandPhraseSimple("いや、何もない。幸運を祈るぜ！","ちょっと見て回っているだけだ。じゃあな。"));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "「どんな質問だ？」";
			link.l1 = "「この書類に書かれている名前に心当たりはあるか？」";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("俺は見慣れねえ書類なんざ興味ねえよ。それに、字も読めねえんだ。高利貸しのところに行けよ、 あの悪魔ならきっと読み書きできるぜ。","何のことを言っているのか全く分からねえ。町の連中にでも聞いてみな、船長 "+GetFullName(Pchar)+".","正直、どうやってお力になればいいのか全く分かりません、船長。 "+GetFullName(Pchar)+"。金貸しに聞いてみろ――もしかしたら何か知っているかもしれねえ。");
			link.l1 = "喜んであなたの助言に従うぜ！";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("「でも嘘をついてるんじゃねえか、船長」 "+GetFullName(Pchar)+"?","「それでどうしたっていうんだ、」 "+PChar.name+"?","「あなたのことは忘れない」 "+GetFullName(Pchar)+".")+"さて、今度は何がご用ですか？",LinkRandPhrase("お会いできて光栄です、船長 "+PChar.name,"Glad"+NPCharSexPhrase(NPChar," "," ")+" お会いできて "+GetAddress_Form(NPChar)+" "+PChar.lastname,"はじめまして、船長 "+PChar.name)+"。だが、俺の名前を知るためだけに来たわけじゃねえんだろう？");

            link.l1 = PCharRepPhrase("やりたかった"+GetSexPhrase("","")+" お前らが町と呼んでるこの穴蔵について何か知りたいんだよ！","やりたかった"+GetSexPhrase("","")+" この町について何か知りたい。");
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
					link.l3 = RandPhraseSimple("商談について話したい。","「財政について……」");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "何か助言をくれないか。俺は購入したいんだ "+pchar.GenQuest.Device.Shipyarder.Type+"、それがあんたの町で売られていたと聞いたんだ。まあ、誰かが路上で売っていたらしい。何か知ってるか？";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("待て！今すぐ名を名乗れ！俺は総督の依頼で敵の間者を探しているんだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","止まれ！俺は～の利益のために行動している"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 総督の命令で来た。敵の間者をこの街で探している。","止まれ、友よ！この地の総督が "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 町でスパイを見つけたいと思っている。"),LinkRandPhrase("待て、姐さん！今すぐ自分が何者か教えろ！俺は総督の依頼で敵の間者を探しているんだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","女、君を拘束しなければならない！私はこの街のために行動しているのだ "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" 総督の命令で来た。敵の間者をこの町で探している。","立ち止まれ、美しい女！地元の総督 "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" 町でスパイを探し出したいようだ…"));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("ご存知ですか","聞いたか","聞いたか")+" 最近この辺りの教会が襲撃されたってことか？");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("いや、気のせいだ。もう行くぜ。","いや、何でもねえ――ただ酒場に向かってただけだ。"),RandPhraseSimple("いや、何もない。幸運を祈るぜ！","ちょっと見て回っているだけだ。じゃあな。"));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("ああ、そうだ、俺もほとんど同じくらい嬉しいぜ"+NPCharSexPhrase(NPChar," "," ")+" お前を酒の一杯として見るぜ。好きなことを何でも聞けよ。","話すのが好きかい、船長？俺もさ……特にラム酒を一杯やりながらな。","「はい」 "+PChar.name+"?"),LinkRandPhrase("何の用だ？","なるほど、船長 "+PChar.name+"。あなたは"+GetSexPhrase("","")+" なかなかのおしゃべりだな。 ","お前にくたびれさせられたぜ"+GetSexPhrase("","")+" 質問は後にしてくれ、船長。ラム酒を手伝ってくれたほうがいいぜ。")),PCharRepPhrase(LinkRandPhrase("何を知りたいんだ "+GetAddress_Form(NPChar)+"?","話を聞こう、船長。","急いでくれ、船長。俺は行かなきゃならないんだ。"),LinkRandPhrase("いつでも喜んで"+NPCharSexPhrase(NPChar," "," ")+"  「良い仲間がいること」 "+GetAddress_Form(NPChar)+" "+PChar.lastname+"。言いたいことを言え。","「はい」 "+GetAddress_Form(NPChar)+"?","おしゃべりが好きなのかい、船長？俺もさ……")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("地元の酒場で流行っている噂は何だ？","この地で何が起きてるんだ？","ここで最近何か変わったことはあるか？");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("そこへ案内してもらえるか？","ある場所への行き方がわからないんだ……","道を教えてくれませんか……？");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("ある人物について人々が何を言っているのか知りたいんだ。","「ある人物について人々が何を言っているか知らないのか？」","地元の人々について何か教えてもらいたいんだ。");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "あなたの植民地について、もっと教えてください。";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("俺には大事な用事があるんだ！","お前に用がある。");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("いや、気のせいだ。もう行くぜ。","いや、何でもねえ――ちょうど酒場に向かうところだったんだ。"),RandPhraseSimple("いや、何もない。幸運を祈るぜ！","ちょっと見て回ってるだけだ。じゃあな。"));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "誰について知りたいんだ？";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "総督について。";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "地元の酒場の主人についてだ。";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "港湾長について。";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "地元の店の主人についてだ。";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "気にするな、忘れてくれ。";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("正直言って、あまり詳しくは知らねえが、少しくらいは話せるぜ。","「うちの植民地の何が気になるんだ？」","もちろん。何を知りたいんだ？");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "「ここはどんな町なんだ？」";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "この町を守っている砦について何か知っているか？";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "話題を変えよう。";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "ふざけてるのか？それとも冗談か？画面の右上隅を見てみろ。";
			link.l1 = "ああ、俺が悪かったな。";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "それについては何も知らねえ。";
			link.l1 = "残念だな。";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "ふむ、 "+pchar.GenQuest.Device.Shipyarder.Type+"？今まで聞いたことがねえな……それは一体何なんだ？俺の人生でそんなもの聞いたこともねえぞ"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "「まあ、これは船大工の道具だ」 "+pchar.GenQuest.Device.Shipyarder.Describe+"。町でそんな物を売っている者はいるか？\nもしかしたらな。\nそんな物を持ち歩いている奴を見かけたか？";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "ふむ……ああ、確かにそんなものを持っている奴を見かけたと思うぜ。数時間前にあそこでそれを持って歩いていたな。 面白い道具だったよ、確かに。";
				link.l1 = "それで、そいつはどんな奴だった？どこへ行ったんだ？俺はその道具がどうしても必要なんだ。";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いや、そんなものは見ていない。";
				link.l1 = "なるほど。さて、聞き込みを始めるか！";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"「それが俺に何の関係があるんだ？俺はこの土地の人間だぜ！」","「さて、なぜこんなことで俺を困らせるんだ？俺はこの街に住んでるが、そんなことは何も知らねえぞ！」"),NPCharSexPhrase(npchar,"また俺に何の用だ？俺がスパイじゃないってもう言っただろうが！？","俺はもう地元の人間だって言ったじゃねえか！？"),NPCharSexPhrase(npchar,"おやまあ、またあんたかい！放っといておくれ――あたしゃ地元の者だよ！","なんでまたくだらねえ質問で俺を邪魔するんだ？"),NPCharSexPhrase(npchar,"またか！今度こそ我慢ならんぞ！","頼む、俺のことは放っておいてくれよ、いいか？お願いだ！"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("誰があなたの言葉を証明できるんだ？","ああ、すまない――もう君に聞いたことだったな……","申し訳ない、こんなに人が多くて…","わかった、わかった……",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "誰でもできるさ！聞けよ、なんで俺にしつこく絡んでくるんだ！？問題があるなら総督のところに行って、 自分で解決してこいよ！";
				link.l1 ="ふむ……こんな些細なことであの人を煩わせない方がいいだろう。私はあなたを信じるよ。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "この町の誰か！ "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" 例えば、今ならできる "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"彼","彼女")+" ちょうどそこに立っている。","「ああ、旦那、そうだな、例えば、」 "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" 俺にできるぜ。");					
			link.l1 = "よし、それじゃあ、見てみようか。";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "「ああ」 "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," 確かに地元の者だ。","彼女は確かに地元の人だ。");
			link.l1 = RandPhraseSimple("なるほど"+GetSexPhrase("","")+"。ご協力ありがとうございます。","異常なし。助けてくれてありがとう。");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "実はな、昨日は町の外を散歩していて、結婚指輪を失くしちまったんだ…… "+GetSexPhrase("船長、探していただけませんか？","奥様、どうか、それを見つけるのを手伝ってください！")+"";
			link.l1 = "もちろん "+GetSexPhrase("できるさ！あんたみたいな美人のためなら、俺はなんだってやってやるぜ！","助けましょう。教会は困っている人を助けるよう教えています。")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("いいえ、できません。申し訳ありません。やることが多すぎるんです。","申し訳ない、できないんだ。今思い出した。"+GetSexPhrase("","")+"……まだ片付いていない用事があるんだ……","私は時間がほとんどないから、何も手伝えないんだ……");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Captain","Lady")+"、それは素晴らしいわ！この指輪を探してちょうだい、夫がもうすぐ到着するの\n "+sti(NPChar.LifeDay)+" 数日間も会っていないし、結婚指輪をしていない姿を彼に見られたくないの。";
			link.l1 = RandPhraseSimple("「どこで失くしたって言うんだ？」","「で、いったいどこでそれを失くしたんだ？」");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "街の門を抜けてすぐさ…";
			link.l1 = "さて、それじゃあ探しに行くとするか……";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "ああ、ぜひ頼む。急いでくれ――覚えておけ、残された時間は限られているんだぞ "+sti(NPChar.LifeDay)+" 日間。";
			link.l1 = "覚えている。";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Captain","お嬢さん")+"！本当に嬉しいわ！どうやってお礼を言えばいいのかしら？";
			link.l1 = "「ああ、礼なんていらねえよ――まったくの善意でやったんだ。」";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "「2、300ペソくらいなら、もらって困ることはねえな……」";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "「ああ、」 "+GetSexPhrase("船長、あなたは本当に高貴なお方です","「お嬢さん、あなたは本当に高貴ですわ」")+"！教会で必ずあなたのために祈ります！さようなら…";
			link.l1 = "「さらばだ」 "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "ああ、もちろんだ。ほら―"+FindRussianMoneyString(iTemp)+"。これで全部です。どうぞこの金を受け取ってください……それでは、お別れです。";
			link.l1 = "「さようなら」 "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("いいや、そのことについては何も知らねえ。","俺はこんなことについて何も知らねえ。","何も知らねえ。");
					link.l1 = LinkRandPhrase("「ああ、ありがとう。」","なるほど、ありがとう。","かしこまりました、失礼します。");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("俺はそのことについて何も知らねえが、酒場の常連客に聞いてみな。きっと何か教えてくれるはずだぜ。","何も話せない。酒場で聞いてみな。","特に何も知らないけど、酒場で噂話があったって聞いたぜ。");
				link.l1 = "まあ、少なくとも何かはあるな。";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ――この町の市民として、抜き身の刃を持ち歩くのは控えてもらわねばならん。","聞いてください――この町の市民として、抜き身の刃を持って歩き回るのは控えていただきたいのです。");
				link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"落ち着け "+GetSexPhrase("相棒","娘")+" 武器を手に持って走り回られると、落ち着かなくなるんだよ……","俺は～の時が気に入らねえ "+GetSexPhrase("男たち","誰か")+" 武器を構えたままうろつくなんて、怖いよ……");
				link.l1 = RandPhraseSimple("了解だ。","しまっておく。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}

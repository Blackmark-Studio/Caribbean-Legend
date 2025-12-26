// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " 終わりだ。さあ、ここを立ち去れ。 "+pchar.name+"。私がこの混乱をすべて片付けます。";
					link.l1 = "よし、出航するぜ！";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町は警戒態勢に入り、あちこちであなたを探しています！私があなただったら、ここに長く留まらないでしょう。","衛兵たち全員がお前を探しているんだ。俺は馬鹿じゃねえし、お前と話して危険を冒すつもりはない！","「走れ」 "+GetSexPhrase("相棒","「少女」")+"……兵士たちに蜂の巣にされる前に……"),LinkRandPhrase("何の用だ、この下劣な奴め！？町の衛兵はお前の居場所を把握しているから、逃げられはしないぞ。 "+GetSexPhrase("汚らしい海賊","てめえ、海賊の売女め")+"!","汚い人殺しめ、俺の店から出て行け！衛兵！","俺はお前なんか怖くねえぞ、卑劣な化け物め！すぐに砦で絞首刑にしてやるからな、逃げられると思うなよ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、そんなの俺には問題じゃねえさ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("「黙れ」 "+GetWorkTypeOfMan(npchar,"")+"さもないと、その血まみれの舌を引き抜いてやるぞ！","「へっ、」 "+GetWorkTypeOfMan(npchar,"")+"「お前も海賊を捕まえたいのか？いいか、坊主、大人しくここに座ってりゃ命は助かるぜ……」"));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "何かご用ですか、旦那？";
				Link.l1 = "少し情報が必要でして……あなたにお聞きしたいことがあります。";
				Link.l1.go = "quests";
				Link.l2 = "小さな貸付はいかがでしょうか？";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "いいや、気が変わった。";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "こちらのイヤリングをご覧ください、旦那。ジャングルで盗賊のポケットから見つけたものです。 これは明らかに優れた宝石職人の作であり、この辺境のものではないと確信しております。いかがでしょうか？";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "フォルケ・デルックという名の債務者がいることは存じております。さて、彼の……滞納状況はいかがでしょうか？";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "フォルケ・デリュクの借金について来た。";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "ご依頼の任務を完了しました、旦那。こちらが……あなたのスペイン人の友人です。";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "やっとまともな船長が私の店を訪れてくれましたね。毎月利息を払うために、 私が彼らのドブロンやギニーを畑に植えて収穫しているとでも思っている愚か者たちにはうんざりしていますよ。\n彼らは一銭一銭を監視し、哀れな高利貸しが飢え死にしないために様々な策を講じつつ、 同時に彼らにクリスマス用のガチョウを買う手段を提供していることなど、まるで理解していません。";
				Link.l1 = "あなたの顧客たちは、自分たちの貯蓄を預かる者からそんな言葉を聞いて喜ぶとは思えませんね。";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "聞けよ、じじいハムスター、今こそ全部ちゃんと説明してもらわねえとな！あの船の積み荷に奴隷なんていなかったぞ、 いたのは兵士の一団だけだ！あいつら相手にするのは本当にきつい任務だったんだぜ！俺はすげえ怒ってるから、 ちゃんと説明しやがれよ！\n";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "おお、やっと来てくれましたな！あなたの大胆な襲撃について、この群島中が噂しておりますぞ。 お会いできて嬉しいです！";
				Link.l1 = "私はそんな名声よりも無名でいたい……あまりにも危険すぎます。";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "私の五千人の奴隷を連れてきましたか？";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "あります。私の貨物室にあります。";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "いいえ、まだ作業中です。";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "ふむ……まだ生きているのか？妙だな。しかし、それも長くは続かんぞ。兵士たち！助けてくれ！ここに盗賊がいる！";
				link.l1 = "なんてろくでなしだ！";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "ごきげんよう。私の名は "+GetFullName(npchar)+"。どのようなご用件でしょうか？";
				link.l1 = "おや！旦那、ここで何をしているのですか？";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "おい、てめえ、この野郎。何か名案でも思いついたのか？俺を殺すためにゴロツキでも雇ったか？口を塞ぎたかったのか？ さあ、しゃべれ！";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "おお、船長！どうぞ、今日私が用意した品々をご覧ください。 これはブラックウッドの部下たちから手に入れた物でございます。彼らは新たな遠征のために資金が必要でして、我々 には――利益、そうでしょう？";
				link.l1 = "ブラックウッドは自分の部下たちが発見物を売っていることを知っているのか？";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("「ごきげんよう」 "+GetAddress_Form(NPChar)+"。どうなさいましたか？私はあなたをご存知でしょうか？","お入りください、船長。私の名は "+GetFullName(npchar)+" そして私はこの地の銀行家です。","「はじめまして。」 "+GetAddress_Form(NPChar)+"！私は地元の銀行家です。もしお金のことでお困りなら、お力になれますよ。"),LinkRandPhrase("以前お会いしましたか、船長？私は "+GetFullName(npchar)+"、そして私は地元の銀行家です。","お入りください、船長。私の名は "+GetFullName(npchar)+" そして私はこの地の銀行家です。","「ご挨拶申し上げます。」 "+GetAddress_Form(NPChar)+"。私は "+GetFullName(npchar)+"、地元の銀行家です。"),LinkRandPhrase("「はじめまして」 "+GetAddress_Form(NPChar)+"、私は "+GetFullName(npchar)+" この素晴らしい町の、ただの控えめな銀行家でございます。","決めるのはあなたですよ、船長！私から金を借りたいのか、それとも利子付きで貸したいのか？","旦那船長！私のささやかな事務所にお越しいただき、誠に嬉しく存じます！"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("喜んで！ちょうど町を散歩していて、あなたのところに立ち寄ることにしたんです。","喜んで、お引き受けします、私は "+GetFullName(pchar)+"、はじめまして。",""+GetFullName(pchar)+" 、という名の船の船長 "+pchar.ship.name+" 「お会いできて嬉しいです。ここは銀行ですよね？」"),RandPhraseSimple("はじめまして。私は "+GetFullName(pchar)+"。 という名の船の船長 "+pchar.ship.name+"。私はただあなたのことを知りたかっただけです。","ああ、ここに銀行があるんだな？お会いできて嬉しい、私は "+GetFullName(pchar)+"、自分の船の船長だ。"));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "マッカーサー夫人、ようこそ、お入りください。";
					link.l1 = "「あなたにも、」 "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("お前か！何の用だ、 "+GetAddress_Form(NPChar)+"?","何のご用でいらしたのですか、船長？申し訳ありませんが、あなたの評判では特に魅力的なお客様とは言えません。","おや、またお客人ですか！最初は強盗かと思いましたよ……はは、冗談です。"),LinkRandPhrase("おや！何のご用ですか？ここは銀行であって、酒場ではありませんよ。","ごきげんよう、船長。私はお客様を選ばせていただいておりますので、その点ご承知おきください。","「何の用だ、」 "+GetFullName(pchar)+"？あなたの名声では大きな融資は受けられないことをお忘れなく、覚えておいででしょうか？"),LinkRandPhrase("お金を投資したいとお考えでしょうか、 "+GetAddress_Form(NPChar)+"？あなたに融資を確保するのは容易ではありません。","Captain "+GetFullName(pchar)+" つまらない銀行家に何をお望みですか？申し訳ありませんが、あなたに融資を手配することはできません。 利子付きでお金を貸せるのは私だけです。","「お入りください。」 "+GetAddress_Form(NPChar)+"。申し訳ありませんが、あなたはあまり歓迎されているお客様ではございません。しかし、 私は普段すぐに人を追い返すことはいたしません。")),LinkRandPhrase(LinkRandPhrase("こんにちは、旦那 "+GetFullName(pchar)+"！いつでもお取引のご相談に応じる用意がございます。","こんにちは、旦那 "+GetAddress_Form(NPChar)+"。私はいつでも融資を行う用意がございますし、いかなる投資も喜んでお受けいたします。","Dear "+GetFullName(pchar)+"！お会いできて嬉しいです！ご用件は何でしょうか？"),LinkRandPhrase("Captain "+GetFullName(pchar)+"！いつでもお力になります。ご融資をご希望ですか、それとも利子付きでご投資なさいますか？","ごきげんよう、船長！あなたはいつでも大歓迎のお客様です。商売の評判も素晴らしいですね！","「ごきげんよう。」 "+GetFullName(pchar)+"。再びお越しいただき嬉しく思います。今回は有益なお取引のご相談でしょうか？"),LinkRandPhrase("ごきげんよう、船長！ご用件は何でしょうか？ご融資をご希望ですか、それともご投資をお考えですか？","Captain "+GetFullName(pchar)+"！有利な条件でお金をお貸ししましょうか？このようなご立派なお客様にお会いできて、いつも嬉しく思います。","またお会いできて嬉しいです、船長！いつでもお力になりますよ、融資でも投資でもご相談ください。")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("冗談じゃねえぞ、銀行屋。こっちは商売やってんだ。","話が長いぜ、相棒。さっさと本題に入ろうじゃねえか。","金に匂いはないって聞いたことがあるかい？だから鼻をつまんで、さあ取引に入ろうじゃないか。"),LinkRandPhrase("「これが顧客への挨拶なのですか？今日は機嫌が良いので運が良かったですね。」","ははっ！俺に会えて嬉しくねえのか？それとも、俺があんたにいい印象を与える金貨じゃねえってのか。まあいい、 商売の話をしようぜ、金貸し。","ええ、礼儀を教えてやりたいところだが、そんな暇はない。代わりに金の話をしよう。")),RandPhraseSimple(LinkRandPhrase("古き友よ、会えて嬉しいぞ！","ここに来るのはいつも楽しいよ、友よ。\nさっそく本題に入ろう。","私もとても嬉しいです。\nさて、商談に入りましょう、旦那。"),LinkRandPhrase("お会いできて本当に嬉しいです。財政の海では何か新しいことがありましたか？","まだ私のことを覚えていてくれて嬉しいです。急いでおりますので、早速本題に入りましょう。","やあ、古き友よ！また会えて嬉しいぞ！")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("ご用件を承りましょうか？","今度は何の用だ？","ふむ……ご心配とは何でしょうか？","「えっ、」 "+GetAddress_Form(npchar)+"……お客様がどれほど厄介か、あなたには想像もつかないでしょう……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("いや、結構だ。俺はただぶらぶら歩いて話してるだけさ。","また俺だ。ちょっと話がしたくてな。","はい、また私でございます。大した用事ではありません、ただ少しお話ししたかっただけです。","ええ、銀行家というのも時に楽ではありません。ちょっとお話ししたかっただけです…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "私たちの財政について相談したいのです。";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "私は宝石や珍しい偶像、または希少な宝石に興味があります。";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "情報が必要なんだ。さて、ちょっと聞きたいことがある。";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "私はあなたに から持ってきた商業書類です "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("私は一人の男の命令でここに来た。その男は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" ここに来るように言われた。あなたから何か受け取る必要がある。");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "ごきげんよう、あなたの息子さんに招かれました。"; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "その書類の持ち主が誰なのか、知りたいのです。";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "あなたの顧客の借金について話したいのです。名前は "+pchar.GenQuest.Noblelombard.Name+"。彼は家宝を質に入れました。私はここで彼の利益を代表しており、その返還についてあなたと話し合う権利があります。 ";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "三か月前に会合があり、ある男の遺品について話しました。彼の名前は "+pchar.GenQuest.Noblelombard.Name+"。覚えていますか？彼は私の名義で預金口座を開かなければなりませんでした。金額は  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "「あなたの…奴隷の任務についてです。」";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "約束通り来たぜ。俺に仕事はあるか？";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "約束どおり来たぜ。仕事はどうだ？";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」 "+npchar.name+"。ご機嫌いかがですか？新しい依頼でもありますか？";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "任務は完了した。逃亡者たちを見つけることができたぜ。だが、そう簡単にはいかなかったがな。";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+npchar.name+"。新たに儲かる仕事をもらいに来た。";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「悪い知らせだ」"+npchar.name+"……ブリガンティンを拿捕できなかった。";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「見てくれ、」  "+npchar.name+"。俺はそのブリガンティンを追いかけたが、書類は見つからなかった。本当にそこにあったのか？";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「良い知らせだ」"+npchar.name+"。あのブリガンティンを追い詰めて書類を取り戻した。これがそれだ。";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」 "+npchar.name+"。私に新しい依頼をご用意いただけましたか？";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"、例の「ガレオン船」とやらをうまく拿捕できました。";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"申し訳ありませんが、このガレオン船には乗り込めませんでした。";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+npchar.name+"「……金を受け取りに来た。」";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"、任務は完了した。あの野郎ゴンティエは死んだし、奴の乗組員も全滅だ。";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"申し訳ありませんが、フランソワ・ゴンティエを捕まえることができませんでした。 トルトゥーガまで追いかけていたのですが、彼は自分のコルベットで私から逃げ切りました。";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」"+npchar.name+"。私のために用意した新しい任務について教えてください。";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("あなたが金に困っているとも、財産を増やしたいとも思いませんが、何のご用で私の事務所にお越しですか？","今度は何のご用件ですか？","ふむ……ご心配とは何でしょうか？","「えっ、」 "+GetAddress_Form(npchar)+"……お客様がどれほど面倒か、あなたには想像もつかないでしょう……","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("いや、結構だ。俺はただ歩き回って話してるだけさ。","また俺だ。ちょっと話がしたくてな。","はい、また私でございます。大した用事ではありません、ただ少しお話ししたかっただけです。","ええ、銀行家というのも時に楽ではありません。ちょっとお話ししたかっただけです…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "私たちの財政について話し合いたいのです。";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "私は宝石、珍しい偶像、あるいは貴石に興味があります。";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "情報が必要なんだ。さて、ちょっと聞きたいことがある。";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "私はあなたに業務書類を持ってきました "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("私はある男の命令でここに来た。その男は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" ここに来るように言われたんだ。あなたから何かを受け取らなきゃならない。");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "ごきげんよう、あなたの息子さんに招かれました。"; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "その書類の持ち主が誰なのか、興味があります。";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "あなたの顧客の借金について話したいのです。名前は "+pchar.GenQuest.Noblelombard.Name+"。彼は家宝を質に入れました。私はここで彼の利益を代表しており、その返還についてあなたと話し合う権利があります。 ";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "三か月前に会合があり、ある男の遺品について話しました。彼の名前は "+pchar.GenQuest.Noblelombard.Name+"。覚えていますか？彼は私の名義で預金口座を開設しなければなりませんでした。金額は  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "「あなたの…奴隷の任務についてです。」";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+NPChar.name+"、あなたの任務について話しましょう。";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "約束通り来たぜ。仕事はあるか？";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "約束通り来たぞ。仕事はどうだ？";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+npchar.name+"。ご機嫌いかがですか？私に新しい依頼でもございますか？";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "任務は完了した。逃亡者たちを見つけることができたぜ。だが、そう簡単にはいかなかったがな。";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」 "+npchar.name+"。新たに儲かる仕事をもらいに来た。";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「悪い知らせだ」"+npchar.name+"……ブリガンティンを手に入れることができなかった。";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「見てくれ、」  "+npchar.name+"……ブリガンティンを追い詰めたが、書類は見当たらなかった。本当にそこにあったのか？";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「良い知らせだ」"+npchar.name+"。あのブリガンティンを追い詰めて書類を取り戻した。これがそれだ。";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」 "+npchar.name+"。私に新しい任務をご用意いただけましたか？";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"、例の「ガレオン船」とやらをうまく拿捕できました。";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"申し訳ありませんが、このガレオン船には乗り込めませんでした。";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう。」 "+npchar.name+"。金を受け取りに来た。";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"、任務は完了しました。あのゴンティエの野郎も、その手下どもも死にました。";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+"、申し訳ありませんが、フランソワ・ゴンティエを追ってトルトゥーガまで行きましたが、 捕まえることができませんでした。彼は自分のコルベットで私から逃げおおせました。";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "「ごきげんよう」"+npchar.name+"。私のために用意した新しい任務について教えてください。";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "金のドゥブロンやそのための宝箱を買いたいですか？信じてください、とても価値のある投資ですよ。";
			link.l1 = "はい、それはとても興味深いですね。";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "ペソで取引しますか、それともドゥブロンで取引しますか？";
			link.l1 = "ペソでございます。";
			link.l1.go = "items";
			link.l2 = "ドゥブロン金貨のためです。";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "これらの書類を読むには私の多くの時間が必要ですし、私の時間は非常に高価なのです。";
			link.l1 = "「あるいは、」 "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" ペソがあなたの時間に見合う補償となりますかな？";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "かしこまりました。それでは、ごきげんよう！";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "見せてくれ！いや、この名前は見たことがないな。港長に見せてみな。";
				link.l1 = "申し訳ありませんが、我々は取引をしたはずです！あなたはこの船長について教えてくれると約束しましたよ！";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" 彼は腕利きの密輸業者だそうです。それが聞きたかったことですか？";
				link.l1 = "そのようですね……";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"これらの書類は我々の植民地巡回船のために署名されたものであり、その船長は強い信念で知られております。";
				link.l1 = "「巡回隊か？司令官の命令で？」";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "私はあなたにあの書類を確認するとだけ約束しました。それ以上はしません。もう行ってよろしいです。";
			link.l1 = "……まあ、ありがとう。";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "ご判断にお任せします。我々の司令官は、長い間この人物にかなり「関心」を示してきました。 もう何かお考えはありますか？そしてここには、印のない船荷証券もございますが…";
			link.l1 = "なるほど。感謝いたします！";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"先ほども申しましたが、その証文の持ち主は信念のある方でして、地元の犯罪にはあまり関わりたくないのです。";
			link.l1 = "なるほど。感謝いたします！";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "ああ、あなたが私の放蕩息子とその若き花嫁を連れてきた船長ですね？";
				link.l1 = "はい、彼らの脱出を手助けしたのは私です。";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "おや、ここにいらっしゃいましたね、私の恩人。ご褒美をお待ちですかな？";
				link.l1 = "お礼の言葉だけで十分ですが……";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "私の子供を助けてくださり、あの厄介な状況に置き去りにしなかったこと、心より感謝いたします。\nどうか、せめてものお礼をさせてください。\nこのささやかな金額と、私からの小さな贈り物をお受け取りください。";
			link.l1 = "感謝いたします。この若いご夫婦のお手伝いができて光栄でした。";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感謝だと？何に対してだ？この間抜けは半年も無職だったくせに、もう女を作る暇があったんだぞ！ 俺があいつの歳の頃は自分の商売をやってたもんだ。嫁にできる総督の娘がいるってのに、 こいつはこの娼婦を連れてきやがった――神よ、こんなこと口にしてすまん！それで今度は俺の祝福を求めてるってのか！";
			link.l1 = "あなたは感情なんて信じていないんですね？";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "感情だと？どんな感情だ？お前も大人の男なのに感情の話か？若者に媚びるとは情けない。お前はあの娘を親元から奪い、 私の息子の人生を台無しにした。俺から感謝の言葉はないぞ。さらばだ。";
			link.l1 = "それでは、失礼します……";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "話し合いましょう。お聞きします。";
				}
				else
				{
					dialog.text = "う、うむ。申し訳ありませんが、お断りしなければなりません。 "+GetAddress_Form(NPChar)+"。申し訳ありませんが、私の銀行はスペインの敵にはサービスを提供しておりません。";
					link.l1 = "金に国籍はありませんよ、旦那銀行家。";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "「うむ、」 "+GetAddress_Form(NPChar)+"。お知らせしなければなりませんが、お預けいただいた保証金はもはや有効ではございません。";
							Link.l1 = "「何の根拠で！？」";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "話し合いましょう。お聞きします。";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "あなたに借りがある "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase("、私はあなたのお金を返す準備ができています","。借金を返済したいのです。","……ついに、清算の時が来ましたね。");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("少し金を借りたいのですが。","どうしてもペソが必要なんだ。","小さな貸付はいかがでしょうか？");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("利子を得るためにお金を預けたいのですが。","私の銀貨をいくつか袋ごと預かっていただけますか？","「万が一の時のために、銀貨をお預けしてもよろしいでしょうか？」"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "利子付きでドゥブロン金貨を預けたいのだが。";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("私の投資をペソで回収しに来たんだ。","そろそろ俺に借りている銀貨を返してもらおうか。","私の投資を利息も含めてペソで返してもらいたい。");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("ドゥブロンで投資した分を回収したいのです。","そろそろ俺に借りてる金を返してもらう時だ。","私の投資したドゥブロン金貨を、利息も含めて返してもらいたい。");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "私は自分の借金を覚えておりますが、まだ返済する準備ができておりません…";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "私の勘違いでした、あなたとは金銭の用事はありません。ごきげんよう。";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "いいえ、お力にはなれません。この厄介な場所では投資のみ受け付けております。\n銀ペソか金のドゥブロンで投資できます。";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "ペソを投資したいので、金額について話そう。";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "ドゥブロン金貨を投資したい。\n金額をはっきりさせよう。";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "興味はありません。";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"あなたの名前は "+GetFullName(pchar)+"、だろう？お前は "+RandPhraseSimple("悪い評判 ","悪い評判 ")+" そして、私はあなたと取引したくありません。";
				link.l1 = RandPhraseSimple("「男だって間違えることくらいあるだろ？」",RandSwear()+"どうでもいいぜ！");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "ああ、いつでも歓迎いたします。ご希望の金額はおいくらですか？";
			Link.l1 = "「小さいものを。」";
			Link.l1.go = "Small";
			Link.l2 = "「適度。」";
			Link.l2.go = "Medium";
			Link.l3 = "できるだけ大きく。";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "素晴らしい！少額の取引なら、いつでもずっと楽です――双方にとってリスクが少ないですから。ご提案できるのは "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "取引成立だ。それで、あんたの取り分はどうする？";
			Link.l1.go = "Interest";
			Link.l2 = "私にはうまくいきません。\n変えましょう。";
			Link.l2.go = "Loan";
			Link.l3 = "私のせいで借金を抱えるのはやめておいた方がよさそうですね。では、ごきげんよう。";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "問題ありません。そう願っております "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" あなたの問題解決にお力添えいたします。これはかなりの大金でございます。";
			Link.l1 = "取引成立だ。で、お前の取り分はどうするんだ？";
			Link.l1.go = "Interest";
			Link.l2 = "私にはうまくいかない。\n変えましょう。";
			Link.l2.go = "Loan";
			Link.l3 = "借金には近づかない方がよさそうだな。さらばだ。";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "うむ……危険だな。よろしい、あなたに貸付を認めましょう、その額は "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+"。ご理解いただきたいのですが、船長、これは本当に多額の金額でございます。どうか真剣にお考えください。";
			Link.l1 = "取引成立だ。それで、あんたの取り分はどうするんだ？";
			Link.l1.go = "Interest";
			Link.l2 = "私にはうまくいかない。\n変えましょう。";
			Link.l2.go = "Loan";
			Link.l3 = "借金からは遠ざかっていた方が良さそうだな。さらばだ。";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest), 1)+"月利は%%です。あなたについて私が知っている限り、これ以上の条件はご提示できません。"; 
			Link.l1 = "問題ない。時間について話そう。";
			Link.l1.go = "Period";
			Link.l3 = "借金には近づかない方がよさそうだな。さらばだ。";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "「私があなたについて知っていることを考慮すると、」 "+Pchar.name+"、この貸付金の返済をお待ちいたします "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+"。その後、私が然るべき措置を取ります。ご理解いただけると幸いです。"; 
			Link.l1 = "喜んであなたの条件……そしてお金もお受けいたします。";
			Link.l1.go = "LoanGranted";
			Link.l3 = "申し訳ありませんが、それは私には合いません。では、ごきげんよう。";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "心から嬉しく思います。しかし、ひとつ忠告させてください。私はこの仕事を長年やっておりますので、 投資を回収する術は心得ております。ですから、もし愚かな考えをお持ちなら、やめておいた方がよろしいでしょう\n気を悪くしないでください、ただの警告です。";
			Link.l1 = "ふむ……では。ごきげんよう。";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "選ぶのはあなたですよ、船長。私の利息は増え続けていますし、あなたにはあまり時間が残されていません。";
			Link.l1 = "気にするな。またな。";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("素晴らしい！コインが必要な時はいつでも私のところへお越しください。いつでもお力になります。","感謝いたします。期日通りに借金を返済できる方とお取引できるのは、いつも喜ばしいことでございます。 時には事情もございますし、私も理解しておりますが……やはり問題は早めに解決していただきたいものです。","「ああ、あなたを信じて正解でした」 "+GetAddress_Form(NPChar)+"！これが私のサービスをご利用いただく最後にならないことを願っております。あなたが誠実な方だと分かりましたので、 今後はさらに有利なお取引をご提案できるかもしれません。");
			Link.l1 = LinkRandPhrase("お金を借りたいのですが。","本当にペソが必要なんだ。","小さな貸付はいかがですか？");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("私の資金を投資したいのですが。","海賊の戦利品を取っておくつもりか？","「万が一の時のために、銀貨をお預けしてもよろしいでしょうか？」");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "利子を得るためにドゥブロン金貨を投資したいのです";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "「ごきげんよう」 "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("賢者のお方ですね！いかほどご投資なさいますか？","よろしい。ご安心ください、この金額は利息とともに安全にここでお預かりいたします。","あなたはこの人生で本当に大切なものをよくご存じのようですね。どれほどご投資なさいますか？");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "冗談かい？";
				link.l1 = "私の失敗でした。";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "うーん、残念ながらそんな大金はお持ちでないようですね。真面目にいきましょう……";
				link.l1 = "結構です。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "よろしいでしょう。私がご提案できるのは……そうですね……"+fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest), 1)+" ％。もちろん月ごとです。";
			Link.l1 = "私には問題ありません。";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "金額を変更したほうがよさそうですね。";
			Link.l2.go = "Deposit";
			Link.l3 = "これは悪い考えだったようだ……さらば。";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "失礼します、船長。しかし、この金額は私の植民地銀行には大きすぎます。利息をお支払いすることができません。 それに、信頼できる護衛もおりませんので……ご理解いただければ幸いです。いずれにせよ、私がお引き受けできる最大の金額は\n "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "残念だが、他の銀行家を探さなければならないな。";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "今や、どんな荒れ狂う嵐に遭っても、一文無しになることはありませんよ。";
				Link.l1 = "わかりました。それでは。";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "約束した利息と経過した時間を考慮すると、私はあなたに借りがある "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"…本当にその金を受け取ってよろしいのですか？";
			Link.l1 = "もちろんです。私にお渡しください。";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "私の金の一部を引き出したいのです。";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "ごもっともです。しばらくの間、お手元に置いておきましょう。良い一日を。";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "「それで、おいくらですか？」";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "「なんてくだらない冗談なんだ、旦那！」";			
				link.l1 = "くそっ！本当に申し訳ありません……金額を変更しましょう。";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "あなたの口座にはそれほど多くの金はありません。";			
				link.l1 = "くそっ！俺のミスだ。金額を変更しよう。";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "全部ですか？わかりました、おっしゃる通りにいたします。こちらがお金です。";			
				link.l1 = "ありがとうございます！";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "よろしい。持っていけ。これがあんたの金だ。";			
			link.l1 = "ありがとうございます！";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "ああ……失うのは本当に辛いな。この金にはすっかり慣れてしまったよ。それでも、また来てくれ。";			
			Link.l1 = "必要ならそうしよう。では、さらば。";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("賢者をお見受けします！どれほどの金額を投資なさいますか？","よろしい。ご安心ください、この金額はここで安全に、利息もすべて付けてお待ちしております。","あなたはこの人生で本当に大切なものをよくご存じのようですね。どれほど投資なさいますか？");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "冗談かい？";
				link.l1 = "ふむ、私の勘違いでした……";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "うーん、残念ながらそんなに多くの金はお持ちでないようですね。真面目にいきましょう……";
				link.l1 = "ふむ……よろしい。";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "よし。私がご提案できるのは…そうですね…"+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" ％。もちろん月ごとです。";
			Link.l1 = "私には問題ありません。";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "金額を変更したほうがよさそうですね。";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "やはり金は手元に置いておいた方が良さそうだ。さらばだ。";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "失礼いたします、船長。しかし、この金額は私の植民地銀行には大きすぎますので、 利息をお支払いすることができません。それに、信頼できる護衛もおりませんし……ご理解いただけると幸いです。いずれにせよ、私がお引き受けできる最大の金額は\n "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "残念だが、別の銀行家を探さねばならんな。";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "今や、どんな激しい嵐が来ても、一文無しになることはないとご安心ください。";
				Link.l1 = "結構です。では、ごきげんよう。";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "約束した利息と経過した時間を考慮すると、私はあなたに借りがある "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"…本当にお金を受け取ってよろしいのですか？";
			Link.l1 = "もちろんです。私にお渡しください。";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "私の金の一部を引き出したい。";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "おっしゃる通りです。しばらくの間、お預けしておきましょう。良い一日を。";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "「で、いくらだ？」";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "なんと愚かな冗談だ、旦那！";			
				link.l1 = "くそっ！本当に申し訳ありません……金額を変更しましょう……";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "お客様の口座にはそれほど多くの金貨はございません、旦那。";			
				link.l1 = "くそっ！俺のミスだ。金額を変えよう…";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "全部ですか？よろしい、仰せの通りに。こちらがお金です。";			
				link.l1 = "ありがとう！";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "よろしい。持っていけ。これが金だ。";			
			link.l1 = "ありがとうございます！";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "ああ……失うのは本当に辛いな。この金にはすっかり慣れてしまったよ。それでも、またお越しください。";			
			Link.l1 = "必要ならそうする。では、さらば。";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "まだ生きているのか？金を返しに来たのか？くそっ！お前のせいで失った金は、お前ごときには絶対に返せない額だ！ お前の死体を見るまでは、俺は決して安らげんぞ！";
            Link.l1 = "私はただ平和的に物事を解決したいだけです。";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("よろしい、では見せてもらおう！お前も死から逃れられぬことを知っておけ！","脅しか！？それじゃあ、お前がどうするつもりか見せてもらおうじゃねえか…","金は我々の人生で最も大切なものではありません。あまりくよくよしすぎず、人を殺すようなことはしないでください。 さあ、どうぞ、挑戦してみなさい。");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "出て行け！二度とお前の顔なんか見たくない。";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "「本当ですか？それで、ご心配とは何でしょうか？」";
			Link.l1 = "本日は、私があなたに借りができました "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+"。そしてこの金をあなたにお渡しいたします。";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "私はあなたとの良好な関係を再構築するために、私の借用証書をお渡しいたします。それは "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "そうこなくちゃ！やっぱりあんたとは商売ができるな。";
			Link.l1 = "ありがとう。もう二度とあなたを失望させません。";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "おいおい、勘弁してくれよ！俺たちは真面目な人間だろう？お前も俺も、 たった一枚のドゥブロン銀貨のために命を投げ出すような馬鹿どもよりずっと上等だぜ。 あいつらは二枚に増やそうとすらしねえんだからな\n俺は今、真剣な商売を持ちかけられる男を探している。勇敢で行動力があり、正直で時間も守るが……まあ、道徳的なジレンマにあまりこだわりすぎない、そんな男だ。そして俺は、お前こそがその男だと期待しているんだ。 ";
			Link.l1 = "それは、あなたがどのような「取引」を私に提案されるかによります。";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "よろしい、では聞いてくれ。今やカリブ海で最も儲かる商売は奴隷取引だ。私はプランターではないが、 信頼できる顧客がいるんだ\nだから、必要なのは次の数の奴隷だ―― "+pchar.questTemp.Slavetrader.iSlaveQuantity+" 首だ。1つにつき250ペソを支払う用意がある。信じてくれ、それは公正な値段だ。合計で君が得るのは "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+".";
			Link.l1 = "いいえ、私は奴隷商人ではありません。良心を無視しない別の助手を探してください。";
			Link.l1.go = "exit_slaves";
			Link.l2 = "魅力的な提案だな。それをやってみたいぜ。奴隷はどれくらい早く必要なんだ？";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "ふん、誰も自分の尻を動かして足元の金を取ろうとしねえみたいだな。がっかりだぜ。\nじゃあな、俺たちの話を噂にするんじゃねえぞ。俺の手は長いんだからな……";
			Link.l1 = "「お前の手は“汚い”な……その口と同じだ。さらばだ。」";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "時間の制限は設けませんが、できるだけ早く任務を達成してください。「黒い象牙」の需要は非常に大きいのです。 うまくやってくれれば、今後も時々この手の仕事を任せることになるでしょう。";
			Link.l1 = "いいだろう。さて、良い知らせを待っていてくれ。";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "「“黒い象牙”の積荷を手に入れることに成功しましたか？」";
            if (amount < 0)
			{
				Link.l1 = "まだです。ただ、我々の契約がまだ有効かどうか確認しているだけです。";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "あります。すべて私の積荷に入っています。";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "素晴らしい。私の部下が品物を引き取ります……税関や要塞の司令官のことはご心配なく。私はここで大規模な事業を運営しておりますので、問題は起こりませんし、 密輸の疑いをかけられることもありません。";
			Link.l1 = "ここでかなり有利な立場を築いているようですね……それで、私の支払いはどうなりますか？";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "ほら、これだ。私は無駄口は叩かんよ。私と取引を続ければ、船長、 すぐにガレオン船が必要なほどの金貨が手に入るだろう！";
			Link.l1 = "それは素晴らしいな、はは……次はどうする？";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "次か？三週間後にまた来てくれ。今ちょうど取引を進めているところでな、その頃には準備が整っているはずだ。";
			Link.l1 = "承知しました、取引成立です。では、ごきげんよう。";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "仕事はあるが、お前の船は弱すぎる。この任務に失敗してほしくないし、お前を死地に送りたくもない。 まだ時間はあるから、せめてバーケンティンやブリガンティン、ブリッグ、 フリュートのようなもっと大きな船を手に入れるんだ。\n時間を無駄にするなよ！";
				Link.l1 = "なるほど、私が対処しましょう。それでは。";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "やっと来たか！待っていたぞ。さて、本題に入ろう。ご存知の通り、どんな商売にも常に競争相手がいるものだ……私にもな。あの強欲で抜け目のない連中は、いつも私から客を奪おうと狙っている！実は、そのうちの一人を排除して、 ついでに一儲けしたいのだ。";
				Link.l1 = "お話を伺いましょう。";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "実に素晴らしい。それでは聞いてくれ。この悪党の名は "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+"、アフリカから奴隷を連れてきて、停泊したのは "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+"、それは「」という島にある "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+"。彼はそこで密輸業者を待っている。彼のガレオン船の名は『"+pchar.questTemp.Slavetrader.ShipName+"。どんな手を使っても、奴らの取引は潰さねばならん！";
			link.l1 = "奴隷たちはどうするんだ？沈めてしまうのはもったいないじゃないか！";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "なぜそんなことを？そんな必要はありません。 "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 悪評が立っていて、奴が消えても誰も気にしないだろう。奴のガレオン船に乗り込み、 そいつを殺して確実に息の根を止めてくれ。積み荷を持ってきたら、私がそれを売ろう。私の情報によれば、 奴隷はおよそ千五百人ほどいるらしい。";
			Link.l1 = "おったまげたぜ。なかなかの額じゃねえか。俺の支払いはどうなってる？";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "いいえ、旦那、こういった陰謀ごとは私には向いておりません。 なぜ私が密輸業者との関係をわざわざ悪くしなければならないのですか？";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "ふむ……どうやらお前のことを見誤っていたようだな……さらばだ、そして今の話は忘れろ。ここで聞いたことを他言するんじゃないぞ。俺はこの町の主だ。もしお前が『"+pchar.questTemp.Slavetrader.ShipName+" 自分のためにも……必ずお前を絞首台に送ってやる。よく考えるんだな。";
			Link.l1 = "ご心配なく、当局には通報しませんし、あなたのガレオン船も必要ありません。では、ごきげんよう。";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "貨物の場所はすでにお伝えしましたし、「獲物」を探して航海する必要もありませんので、報酬は少し低くなります――一人頭200ペソです。それでも、これは大金ですよ――成功すれば三十万ペソと船が手に入りますからね。";
			Link.l1 = "承知した。猶予はどれくらいありますか？";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "ほっほっ！まるでその奴隷どもが自分から俺の船まで泳いできて、 さっさと貨物に入りたがってるみてえな言い方じゃねえか！ 俺の連中がそんなはした金のために命を張ると本気で思ってんのか？報酬を上げろ、さもなきゃこの仕事から手を引くぜ。 ";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "二週間の猶予だ。遅れるんじゃないぞ、さもないと奴は積み荷を移して全てが終わっちまう。";
			link.l1 = "それなら急がねばならんな。良い知らせを持って戻ると期待していてくれ。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "「さて、」 "+GetFullName(pchar)+"「で、我々の任務はどうなった？その暗い顔を見る限り、失敗したようだな。」";
			link.l1 = "くそっ、お前の言う通りだ……俺は……その、分かるだろ……遅れちまったんだ。もうあいつはそこを離れたみたいで、誰も見つからなかった。 ずっと風まかせで航海しなきゃならなかったぜ、ちくしょう…… ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "「さて、」 "+GetFullName(pchar)+"、今日はどんな稼ぎがあったんだ？聞いたところによると\n "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 魚のエサになるんだぜ！ハハハ！";
			link.l1 = "「ああ、まさに間に合った！」 "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" 密輸業者の船に奴隷を移していたんだ。両方とも乗り込んで、デイヴィ・ジョーンズの元に送ってやったから、 今じゃあんたの競争相手が減ったぜ。";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "ああ、どうやらお前については俺の勘違いだったようだな。遅れたのか？それとも戦うのが怖かったのか？まあ、 どっちでもいい。今となっては何の意味もない。消えろ。もうお前には用はない。ここで見聞きしたことはすべて忘れろ。 ";
			link.l1 = "それでは、ごきげんよう。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "やはりお前は俺の見立て通りだったな― "+GetSexPhrase(" あなたは粋なごろつきですね"," お前は勇ましい娘だ")+"！お前のような男が必要だ。任務は実に見事に果たしたな――なんと千五百人以上もの奴隷を連れてきたとは！\n残念だが、私が支払えるのは千六百人分だけだ。残りの分を払うだけの金貨はないので、自分で売るしかないぞ。 報酬は三十二万ペソだ。";
				link.l1 = "ありがとうございます。お取引できて光栄でした、 "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "やはりお前は俺の思った通りだったな― "+GetSexPhrase(" あなたは粋なごろつきだ"," お前は勇ましい乙女だ")+"！お前のような男が必要だ。任務を見事に果たしてくれたな――私のもとに連れてきてくれた "+sTemp+" 奴隷たち。あなたの報酬は "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "ありがとうございます。お取引できて光栄でした。 "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "少なくとも、最も困難な状況を名誉を保ったまま生き延びましたね。賞金は私の期待より少ないですが、 それでも満足しております。あなたは持ち帰ってくれました "+sTemp+" 奴隷たち。あなたの報酬は "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "ありがとうございます。お取引できて光栄でした。 "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "なるほど……それは理解できますが、私はもっと多くを期待していました。あなたが持ってきたのはたった "+sTemp+" 奴隷たちか。少なくとも、あなたは私の競争相手を排除してくれた、それだけでも価値がある。あなたへの報酬は  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "感謝いたします。ご理解に感謝しております。 "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "素晴らしい話だが……ふむ。どうやら君について勘違いしていたようだ。何を持ってきたのかね？ "+sTemp+" 奴隷だと？じゃあ、他の連中はどうした？まさか沈めたなんて言うなよ。どうせ密輸業者に売り飛ばしたか、 もっと悪いことに、あのラヴォワジエの野郎に渡したんだろう。さっさと出て行け、もうお前とは関わりたくねえ！";
				link.l1 = "かしこまりました、それでは失礼いたします。";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "いい話に聞こえるが……俺たちの奴隷はどこだ？積み荷はどこにある？まさか沈めたなんて言うなよ。どうせ密輸業者か、 最悪あのラヴォワジエ野郎に売り飛ばしたんだろう。失せろ、もうお前には用はねえ。";
			link.l1 = "ご要望通り、さようなら。";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "これで終わりじゃねえぞ。俺を騙そうなんて、誰にもできねえ！その企みの代償は払わせてやる――必ず面倒な目に遭わせてやるからな。さあ、とっとと失せろ！";
			link.l1 = "てめえとその奴隷売買なんざ、くたばっちまえ！ここで斬り捨ててやってもいいが、 俺はお前なんかよりずっと上等な男だからな。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "「どうやら私たちはうまく協力できているようですね。」 "+pchar.name+"。とても嬉しいです。1か月後にまたお越しください。もしかするとあなたにぴったりの仕事を用意できるかもしれません。 すでにいくつか案があります。";
			link.l1 = "ええ、また一か月後にお会いしましょう。\nあなたと取引するのは非常に利益になります。";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "それはあなたに莫大な富をもたらします……最後にもう一つだけ質問させてください、 "+pchar.name+"「ガレオン船の船室で、何か変わったものを見つけましたか？」";
			link.l1 = "特に何もありませんよ……私が何か見逃しましたか？";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "「この古いバックル、いわゆる“サソリ”のお守りのことか？」";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "もしかしたらやったかもしれないし、やらなかったかもしれない……今となってはどうでもいいさ。\n一か月後にまた会おう。さらばだ！";
			link.l1 = "「では、また」 "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "その通り！これはメディチ家のフィブラだ……ご存じかな？つまり、やはりあのろくでなしの船室にあったということだ……ちょっと見せてもらってもいいかな？";
			link.l1 = "もちろん、持っていけ。";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "ほう、ほう……本当にそうだな。聞いてくれ、 "+pchar.name+"「それを私に売ってください。十万ペソをお支払いする用意がございます。」";
			link.l1 = "十万か？ふむ……承知しました。どうぞ！";
			link.l1.go = "Buystatue";
			link.l2 = "いいえ、これは売りません。このフィブラの本当の価値は銀や金では測れませんから。 こういう物事の仕組みはよく知っています。";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "完璧です！取引が成立して嬉しいです。お金をお受け取りください。\nまた一ヶ月後にお会いできるのを楽しみにしております。";
			link.l1 = "「ごきげんよう」 "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "ご覧の通り、私はこのフィブラがどうしても必要なのです！まったくあなたの言う通り、 これは金銭で価値を測れるものではありません。愚かな商人なら五千でも買わないでしょう。しかし、 あなたはその真価をよくご存じのようですね、そんな額では売らないのですから。\nもしお金がご不要なら、交換はいかがでしょう？あなたの興味を引くものがございます。さあ、ご覧ください。 見事な軽装鎧です！ご自身の目で確かめてください！この鎧をフィブラと交換で差し上げます。\nちなみに、これは唯一無二の品ではありません。あなた方水夫なら、また手に入れることもできましょうが、 私にはできません。これでご納得いただけますか？";
			link.l1 = "へぇ…まあ、そうだな。鎧を渡してくれ、代わりにこの留め金を持っていけ。";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "いいえ、このフィブラはこの鎧よりも私にとってはるかに価値があります。私自身のために取っておきます。";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "素晴らしい！取引が成立して嬉しいです。これがあなたの鎧です。どうぞお持ちください。\n一か月後にまたお会いしましょう。ごきげんよう。";
			link.l1 = "では、また。 "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "残念だな……本当に残念だ。まあ、持っていけ。俺は咎めやしないさ。ひと月後にまた会おう。さらばだ。";
			link.l1 = "ごきげんよう。";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "「ちょうどいい時に来ましたね。」 "+pchar.name+"。任務を用意しております、もし始めるご準備ができていれば。";
			link.l1 = "もちろん、準備はできております。";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "素晴らしい！さて、本題に入りましょう。最近のニュースはご存知ですか？";
			link.l1 = "ふむ、どういう意味ですかな？毎日たくさんの知らせが入ってきますので。";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "これはまさに我々の商売に関わる話です。新大陸の歴史上最大規模の奴隷逃亡事件が起きました！ 千人以上の者たちが脱走し、その間にオランダのいくつかの前哨基地を破壊し、焼き払ったのです。\n";
			link.l1 = "興味深いですね。続けてください。";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "しかし、奴らはただ逃げただけじゃなく、どうにかして島を出て行ったんだ！跡形も残っていない。 マティアス・ベックは激怒している。だが、それが問題じゃない……問題は、君にキュラソーへ航海してもらい、そこで何が起きたのか調べ、 逃亡者たちの行方を突き止めて捕らえてほしいということだ\nそしてもちろん、オランダの無慈悲な裁きの手から奴らを救い出してほしい。１人につき３００ペソ払おう――奴らはとても良い奴隷になると聞いているからな。";
			link.l1 = "了解だ。これからキュラソーへ向かう。良い知らせを持って戻るのを待っていてくれ。";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "知ってるか、俺はその任務は受けねえ。人々から自由を奪うつもりはない。奴らは命を懸けて自由を手に入れたんだ。 その権利は十分にあるさ。";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "なんと残念なことか……あなたがそんなことをするとは思いませんでした……しかも最悪のタイミングで。\n私たちの協力関係はこれで終わりだということは、もうお分かりでしょう。\nさようなら。";
			link.l1 = "良い一日をお過ごしください。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "はっ！お前は困難な任務をやり遂げただけでなく、俺が頼んだ以上の奴隷まで連れてきたじゃねえか― "+sTemp+" 奴隷。しかし "+sNum+" 奴隷たちはキュラソーから逃げ出していない。1人につき100ペソ支払おう。それで問題ないだろう。報酬は33万ペソであり\n "+FindRussianMoneyString(iSlaveMoneyH)+" 「過剰分についてだ、はは。」";
				link.l1 = "ははっ！お前さんは絶対に騙されねえな。わかった、何でも言う通りにするぜ。 "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "あなたはあの困難な任務を見事に成し遂げ、私のもとに持ち帰ってくれた "+sTemp+" 奴隷たち。あなたの報酬は "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "感謝いたします。お取引できて光栄です、 "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "あの困難な任務を成し遂げましたね。報酬は思ったほど豪華ではありませんが、それでも満足しています。さて、 それをここに持ってきたのですね "+sTemp+" 奴隷たち。あなたの報酬は "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "ありがとうございます。お取引できて光栄でした。 "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "見つけてくれたのか？ふむ……何を持ってきてくれたのだ？"+sTemp+" 奴隷だと？残りの積荷はどこだ？まさか沈めたなんて言い訳はするなよ。どうせ密輸業者に売ったか、 もっと悪いことにイスラ・テソロのラヴォワジエ野郎に売り払ったんだろう。もう出て行け、 これ以上お前とは取引したくない。";
				link.l1 = "ごきげんよう。";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "見つけたのか？奴隷たちはどうした？積み荷はどこだ？まさか沈めたなんて言うつもりじゃないだろうな。 どうせ密輸業者か、いやそれより悪い、イスラ・テソロのあのラヴォワジエ野郎に売ったんだろう。もう出ていけ、 これ以上お前とは仕事をしたくない。";
			link.l1 = "ごきげんよう。";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "心より感謝しております "+pchar.name+"。本当ですよ。1か月後にまたここへ来てください、双方に利益となる新しい商談を用意しておきます。";
			link.l1 = "「私も我々の提携に満足しております」 "+npchar.name+"。では、また一か月後にお会いしましょう。";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "「ちょうどいい時に来てくれました」 "+pchar.name+"。私は勇敢で抜け目のない船乗りを探しているのです、ははは。私の仕事を引き受ける覚悟はありますか？";
			link.l1 = "お話を伺いましょう。";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "今回は非常に簡単です。本日、ピナス船が "+pchar.questTemp.Slavetrader.ShipName+"「の旗の下で」 "+NationNameGenitive(sti(npchar.nation))+" は投錨した "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" 湾だ。現地の密輸業者の手を借りて大量の「黒檀」を積み込んでいた。二千本、間違いない\n乗組員に兵士はいないし、船長は商人だ。全体的にまったく脅威ではない。船を拿捕して積荷を持ってこい。 いつも通り一本につき二百ペソだ。";
			link.l1 = "ふむ……今回は前回の仕事とは違うな。俺に自分の国の船を襲えって言うのか！";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "「わからないな、」 "+pchar.name+"船の旗なんて関係あるのか？本当にそんなこと気にするのか？";
			link.l1 = "俺が気にするか？いや、そんなことどうでもいいさ。金に国籍なんてねえからな。ただ、ちょっと意外だっただけだ……";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "私は気にしています。持ちたくはありません "+NationNameAblative(sti(npchar.nation))+" 私の敵の中で。";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "本気か？冗談だろう、今どき誰も信用できねえんだ…そういうことなら、とっとと失せな。ここで見たことも聞いたことも全部忘れろよ！";
			link.l1 = "「では、また」"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "なぜ驚いているのですか？私がコインの国籍など気にしないからですか？ご安心ください、 実際に私はまったく気にいたしません。正直申し上げて、愛国心などというものは、銀行家としては害にしかなりません。 破産したいのでなければ、ですが\nさて、哲学はこの辺にして本題に入りましょう――船は真夜中までここに停泊しますので、残された時間は多くありません。ご準備はよろしいですか？";
			link.l1 = "「はい」 "+npchar.name+"、私はこれから向かうところだ。";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "素晴らしい。あなたなら我々の任務をきっと成功させてくれると確信しております。ご武運を。"+pchar.name+".";
			link.l1 = "ありがとうございます！ごきげんよう。";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "「さて、」 "+GetFullName(pchar)+"「で、任務はどうなりましたか？その陰鬱な顔を見ると、失敗したようですね。」";
			link.l1 = "まったくその通りだ……俺は……いや……遅すぎたんだ。酒場にいたもんで、出航した時にはもう海には誰もいなかったんだ。";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+"、どうか落ち着いてください。私のせいではありません！くそっ、報告を受け取ったのが遅すぎた……裏切りがあったのです！信頼していた部下の一人に裏切られました！";
			link.l1 = "よし、お前が本当のことを言ってるのは分かった。お前は運がいいな、あのピナス船の船長が俺に「商売」 がバレたと教えてくれたからだ。もしあいつが口を滑らせなかったら、とっくにお前を殺してたぜ。だがな、お前、 この金の亡者め、今までずっと「この町はお前のものだ」なんてほざきやがって！";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "待ち伏せは地元当局が仕組んだものではなかった、そうでなければ私が知っていたはずだ…… "+pchar.name+"、今は争っている場合ではありません。私たち二人とも危険な状況です。 私の以前の取引相手の一人が私たちを陥れました\n集められた証拠――書類の束――が総督のもとへ運ばれていることを突き止めました。もし彼の手に渡れば、我々は終わりです！ちなみに、 一番酷い目に遭うのはあなたですよ。";
			link.l1 = "「今になって、あのろくでなし船長の言ってたことがわかったぜ！」";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "よく聞いてくれ。まだ望みはある。荷物はブリガンティン『"+pchar.questTemp.Slavetraderbrig.ShipName+"。それだけは確かです。書類は総督官邸に届けられています\n "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+"。その船を拿捕して、乗り込んで、証拠となる品を見つけなければならん。";
			link.l1 = "ここではあまり選択肢がないな。俺のためにも、お前自身のためにも祈ってくれ、 そして俺がそれを捕まえられることを願ってくれ。\n戻ったらまたこの件について話そう。俺が簡単に諦めると思うなよ。";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "この包みを手に入れるのが最優先だ！お前が俺に届けるまで安心できねえ……くそっ……"+pchar.name+"……どうやらここで問題が発生したようだな……";
			link.l1 = "何かご用でしょうか？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "くそっ……お前に期待してたんだぜ。 "+pchar.name+"……わかったよ。だが、これで取引は終わりだ。もし調査官に賄賂を渡せなければ、俺は逃げるしかない。 ここに残るのはおすすめしないぜ――いつ兵士が来てもおかしくないからな。じゃあな。";
			link.l1 = "「ごきげんよう」 "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "彼らはそこにいた。さて、これでもう一緒に商売はできませんな、安全ではありませんので。ごきげんよう。";
			link.l1 = "「ごきげんよう」 "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "素晴らしい！あなたならやってくれると信じていましたよ。 "+pchar.name+"。どうかその書類を渡してください、私はあまりにも緊張しています。";
			link.l1 = "持っていけ。";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "よし……これで私は安全だ。総督には何も知られずに済むし、地元当局との問題もすべて片付けたが、かなり金がかかったんだぞ。 ";
			link.l1 = "素晴らしい話だが、お前の軽率な行動のせいで俺が被った迷惑、ちゃんと償ってもらわねえとな？";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "「ええ、」 "+pchar.name+"。さらに、私はあなたに多大な借りがございます。そして、今後もぜひお取引を続けたいと心より願っております。 しかし、どうかご理解いただきたいのです――私は莫大な財産を費やしました――総督や司令官の忠誠心は決して安くはありません。そして、 私の銀行で起きた巡回隊全員殺害事件にも対処せねばなりませんでした……";
			link.l1 = "「つまり、俺の費用を補償してくれねえってことか！？」";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "「そんなに厳しくしないでください」 "+pchar.name+"。実は今、本当に金に困っておりまして、別の形でお支払いを提案させていただきます。";
			link.l1 = "それでは、お話を伺いましょう。";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "私と仲間は一年前、メイン南岸近くで嵐に遭った。俺たちの船はボカ・デ・ラ・セルピエンタ海岸の岩場に打ち上げられ、 すぐに沈んじまったが、なんとか積み荷を岸へ引き上げたんだ。宝石や宝飾品でいっぱいの箱さ。 その入り江はなかなか居心地が良さそうだったから、何の苦労もなく財宝を隠したんだ\nだが嵐が明けた翌朝、インディアンどもに襲われた。生き残った連中のほとんどがそこで死んだよ、俺の仲間もな。 何人かの水夫と俺だけがロングボートで逃げ延びた\nクマナには無事たどり着いたが、財宝を取り戻しに戻る勇気はなかった。あの土地の野蛮人どもが、 今も俺の箱と一緒に岸を守っているに違いない。だが、あんたならあの赤肌どもを片付けられるだろう\nそこにある宝飾品は、南メインへの遠征費用も含めて、あんたの出費をすべてまかなうのに十分すぎるほどだぜ。";
			link.l1 = "ふむ……よかろう。ではクマナへ向かうとしよう";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "「ご安心ください、」 "+pchar.name+"、私が申し上げたことはすべて真実でございます。ひと月後にまたお会いできることを期待しております。 すでに別の取引も考えており、苦境にある私の商売をどう助けるかも思案中でございます。ごきげんよう。";
			link.l1 = "では、また "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "「そして、ここにおいでですね」 "+pchar.name+"。ちょうどいい、いつもながら絶妙なタイミングだ。次の任務を渡す前に、 カリブの奴隷市場についてもう少し情報を伝えたい。\n「レパルティミエント」という言葉の意味を知っているか？";
			link.l1 = "うーん、違いますな。 "+npchar.name+"、違いますよ。しかし、誰かから何かを奪うことについてでしょうか。私の考えは合っていますか？";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "驚いたな。私に何を期待していたのだ？立ち去れ！";
			link.l1 = "違法な商売は私の良心には重すぎます。\n特に奴隷取引はなおさらです。";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "「もう少しでできそうだ」"+pchar.name+"。誰かの自由を奪うことです。レパルティミエントは、現地インディオたちを巧妙かつ合法的に奴隷化する手段なのです。 いわば、そういうことです。スペイン当局は本土の先住民に対してこれを利用しています。もっと詳しく知りたいですか？ ";
			link.l1 = "なぜだ？";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "スペイン王室の使節たちはインディアンの集落を訪れます。冷酷な欺瞞や露骨な脅しを使い、 腐った肉や古いカミソリなど、あらゆるガラクタを法外な値段でインディアンたちに売りつけるのです。 しかも掛け売りで\nしばらくして、例えば一年後、使節たちは再びやって来て代金の支払いを要求します。 インディアンたちが支払えない場合――たいていそうなるのですが――スペイン人は働き盛りの男たちを何人か連れていきます。「しばらくの間、土地の耕し方を教えるため」と称して\nご想像の通り、彼らが集落に戻ることは決してありません。こうして、 うぶな赤い肌の者たちはサトウキビ農園やレッドウッド工場に送られてしまうのです。";
			link.l1 = "くそっ……本当に……インディオたちはそれについてどうしてるんだ？スペイン人に奴隷にされる時、抵抗するのか？ それとも何が起きてるのか理解していないのか？";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "彼らはいつも予感しているのだろうが、実際に公然と反抗する者はごくわずかだ。 特にスペイン人が酋長の指紋入りの書類を突きつけてきた時にはな。もちろん、 こうした手口は大抵アラワク族やミスキート族のような穏やかな部族に対して使われるものだ。だが、 戦闘的なイツァ族やアカウォイ族にはそんな手は通用しないだろう\nさて、あなたの任務について話そう。";
			link.l1 = "もうたくさんの金貨の匂いがしてきたぜ！聞かせてくれ、 "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "間もなくカラカスから大型ガレオン船が出航する。その名は "+pchar.questTemp.Slavetrader.ShipName+"。そこには膨大な数の奴隷――約三千人ものオリノコ川流域のインディオたちが、レパルティミエント政策に基づき捕らえられている。 ガレオン船はサンティアゴへ向かって航行中だ。キューバの砂糖プランテーションには多くの労働者が必要なのだ。 君はそのガレオン船と積荷を奪取しなければならない。俺なら最低でも二隻の船を連れていくだろう。 あのガレオン船は同型の中でも最高級だと言われているからな。\n支払い率は変わらず、一人頭二百ペソだ。 ";
			link.l1 = "へっ！いい話じゃねえか。俺も賛成だぜ。";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "お前のそのレパルティミエントには俺はどうも納得できねえ。あまりにも冷淡すぎるぜ。俺はこんなことやらねえぞ。";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "それでは幸運を祈ります。このガレオンの船長は非常に熟練した戦争の水夫であることを知っておいてください。 簡単な戦いにはなりませんから、覚悟しておきなさい。\n時間を無駄にしないように、彼が到着するまで十五日か二十日ほどかかるでしょう。 "+sTemp+" サンティアゴだ。このガレオン船は本当に目立つから、見逃さないようにな\nああ！危うく忘れるところだった！船にはインディオの装飾品がたくさんあるぞ。 現地人はよく自分たちの信仰具や工芸品で借金を返すんだ。何か特別なものを見つけたら持ってきてくれ。 価値ある品なら一つ一つにしっかり報酬を払おう。";
			link.l1 = "承知しました。";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "「さて、」 "+pchar.name+"……これが私の最後の望みだったのです……だからこそ、この仕事をあなたに頼んだのです。あなた以外にできる者はいないと思っていました……しかし、今となってはあなたにも無理だったと分かりました。では、お別れを言いましょう。最後の失敗と数々 の噂のせいで、私の顧客は皆いなくなりました。私はほとんど破産寸前で、この町を去らねばならないかもしれません。 あなたを責めるつもりはありません――この仕事はあまりにも困難でした。ええ……さようなら。"+pchar.name+".";
			link.l1 = "申し訳ございません。 "+npchar.name+"、それは行き過ぎでした。本当に申し訳ありません。いずれ全てが落ち着くかもしれません。さようなら。";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "ふう、今はもう気分が良くなった……あなたを信じて正解だった……この皮肉はどこから来たんだ？何か問題でも？";
				link.l1 = "旦那、あれはガレオンじゃなかったんだ……いや、大きなガレオンですらなかった……くそっ！あれは戦列艦だったんだ！しかも、あんたは一言も警告してくれなかったじゃないか！だが、 俺はなんとか乗り込むことに成功した。俺は "+sTemp+" 奴隷たちを用意しており、あなたに引き渡す準備ができています。我々の取り決めによれば、あなたは私に― "+FindRussianMoneyString(iSlaveMoney)+"。あなたの誤った情報に対して、何らかの補償をいただけるとありがたいのですが。";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "ガレオン船は見つけたのか？奴隷たちはどうした？三千人いるはずだ、間違いなく！くそっ、 みんな裏切り者でネズミばかりだ！お前だけは信じていたのに……お前は俺の最後の希望だったんだ\nいいだろう……誓ってやる、残った金をすべて使ってでもお前を滅ぼし、殺してやる！全艦隊を "+NationNameGenitive(sti(npchar.nation))+" お前を追い回すことになるぞ！ここから出て行け！";
				link.l1 = "「さて……」";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "なんだって！？誓って言うが、俺は全然知らなかったぜ。出航するのは重ガレオンのはずだったのに、 まさか戦列艦とはな！どうやら土壇場で計画を変えたらしい……だが、それでもお前はやり遂げたんだな！\n金や経費の補償についてはまったく同感だが、実は今その額を持ち合わせていないんだ。 最近の俺のトラブルは知ってるだろう……だが、怒らないでくれ、 "+pchar.name+"頼むからさ、俺に貨物を渡してくれれば、俺が売ってやるよ。もう顧客は待ってるんだ\n五日もあれば全額用意できるから、ちゃんと報酬も渡すさ。俺を信じてくれ。ほら、今持ってる現金は全部渡すよ。";
			link.l1 = "ふむ…今すぐ金を受け取れると思ってたんだがな。俺がどんな修羅場をくぐってきたか、知ってほしいもんだぜ！まあ、いいさ…同情してやるよ。だがな、もし俺を騙そうとしたら、ヨーロッパに逃げても必ず見つけ出すからな！";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "「ご存知でしょう、」 "+npchar.name+"「くたばれ！取引なんかじゃなかったんだ。俺がどんな修羅場をくぐったか、お前には想像もできねえだろ。 奴隷は全部俺が引き取って、お前の仲介なんか使わずに売りさばいてやるぜ。」";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "そうか、やっとその気になったか！どうやら油断している "+npchar.name+" ただの搾取される牛に過ぎなかったのか、少しでも遅れればお前は俺を裏切り、勝手に動き出す。俺がお前に仕事を与え、 獲物の情報を教えたことを忘れたようだな\nよかろう……誓ってやる、残った金をすべて使ってでもお前を滅ぼし、殺してやる！艦隊全体が "+NationNameGenitive(sti(npchar.nation))+" 俺はお前を狩るつもりだぜ！俺の前から消えろ！";
			link.l1 = "空っぽの金庫で俺を脅そうなんて、ふざけるなよ。お前の艦隊全部沈めて、カニの餌にしてやるぜ。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "ご理解いただきありがとうございます。 "+pchar.name+"。ご安心ください、脅しなど必要ありません、すべてうまくいくことをお約束します\nこれは前金です。十五の箱。そのうち五つは精神的損害への補償となります。 残りを受け取るために五日後にまたお越しください\n船で見つけたインディアンの品があれば、必ずお持ちください……もっとも、本当に見つけたのであれば、ですが。いずれにせよ、それらにお支払いできるものはございません。";
			link.l1 = "「五日後に」"+npchar.name+"……五日後に……";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "「約束した通り、」 "+pchar.name+"、お支払いの準備ができております。奴隷は売却され、依頼人も満足、我々も同様です。前金を差し引いた後、 あなたの報酬は"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+"。どうぞ、お金をお受け取りください。";
			link.l1 = "「素晴らしい」 "+npchar.name+"……約束を守る男と取引できるのは気持ちがいいものです……";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "「私の言葉はいつでも信じていただけます」 "+pchar.name+"。私はあなたに疑われるようなことは一度もしていません。パートナー同士、正直であることが商売の要です\nさて、今度はインディアンの遺物について話しましょう。私のような収集家を待たせず、持っている品を見せてください。 ";
			link.l1 = "ふむ……ご覧ください。";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "はい！素晴らしい！黄金の儀式用ナイフだ！これは珍しい品だよ。 こういうものをずっとコレクションに加えたかったんだ。三万で買い取ろう。もしくは「エエカトル」 の護符と交換でもいい。どちらにせよ、あれは二つ持っているからね。";
				link.l1 = "金を受け取るぜ。";
				link.l1.go = "BG_money";
				link.l2 = "「エエカトル」のお守りと交換してもいいぜ。";
				link.l2.go = "BG_change";
				link.l3 = "このナイフは持っていた方がよさそうだな。";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "さて……残念ですが、あなたには私にとって興味深いものが何もありませんね。";
				link.l1 = "おっしゃる通りでございます。";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "素晴らしい。3万を受け取れ、そしてこのインディアンのナイフは今や私のものだ。";
			link.l1 = "よろしい。で、それだけがご所望ですか……";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "素晴らしい！こちらがあなたのお守りです。そしてこのインディアンのナイフは私のものになりました。";
			link.l1 = "よろしい。それで、それだけがご興味なのですか……";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "まあ、どうでもいいさ。しかし、それにしても本当に残念だな……";
			link.l1 = "よろしい。それで、あなたが興味あるのはそれだけですか……";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "待ってくれ！もう一度よく見せてくれ……";
			link.l1 = "ええ、どうぞ。ご覧になって、お好きなものをお選びください。";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "これだ！最初は全然気づかなかったよ。この銅の輪がついた骨に興味があるんだ。実に興味深い品だよ、まったく……。2万ペソで買い取るか、「チマルータ」の護符と交換してもいいが、どうだい。";
				link.l1 = "金を受け取ろう。";
				link.l1.go = "PF_money";
				link.l2 = "交換として「チマルータ」のお守りをもらいたい。";
				link.l2.go = "PF_change";
				link.l3 = "この遺物は俺が持っておくぜ。";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "いいえ……ここには他に興味深いものは何もありません。";
				link.l1 = "どうでもいいさ！";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "素晴らしい！こちらが2万ペソだ。そしてこの骨は私のものになる。";
			link.l1 = "良いですね。我々の取引には満足しています。";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "素晴らしい！こちらがあなたのお守りです、そしてこの骨は私のものになります。";
			link.l1 = "良いですね。今回の取引には満足しています。";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "まあ、どうでもいいさ。しかし、やっぱり残念だな……";
			link.l1 = "その骨は俺自身が必要なんだ、すまねえな。";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "「ええと……ガレオン船、いや、戦列艦に乗り込んでくださったおかげで、私は救われました。本当に、我々 の協力関係に感謝しております。」 "+pchar.name+"。あなたは私の最良の代理人です。";
			link.l1 = "光栄でございます。私の業績を少々過大評価なさっているのではありませんか……";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "私はまったく本気です。そして、あなたの卓越した能力と私の信頼ゆえに、 もう一つ任務を引き受けていただきたいのです。";
			link.l1 = "へえ！驚きましたな！お聞きしましょう。他の奴隷を乗せたガレオン船はどこにありますかな？";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "今回は奴隷の件ではありません。驚きましたか？この任務には十分な報酬をお支払いします……本当に。";
			link.l1 = "早速本題に入りましょう。";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "この件は、あなたも関わった最近の出来事と繋がっております……ご存知の通り、私はやや違法な商売――奴隷取引に手を染めております。そして、あなたのような私掠船乗りを様々な任務に雇っていることもご存知でしょう\nつい先日、私の部下の一人が理由も分からぬまま私を裏切り、証拠を集めて当局に報告しました。 その結果をあなた自身の目でご覧になったはずです。兵士を乗せた船がここに到着し……あとはご存知の通り\n事態を収拾するのにはかなり骨が折れました。ご理解いただけると思いますが、 この裏切りを見過ごすわけにはいきません。それに、 あのネズミがまだ生きていると思うと安心して暮らすことも働くこともできません。賞金稼ぎも差し向けましたが、 未だ成果はありません\nそこで、あなたにこの件を直接解決していただきたいのです。なにしろ、 あの男の行動はあなたにも影響を及ぼしたのですから。";
			link.l1 = "ふん…あの野郎は帆桁に吊るされるべきだぜ！そいつについてもっと詳しく教えてくれ、もちろん仕事の報酬についてもな。";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "その点については心配いりません。彼の始末には十分な報酬をお支払いしますし、それは金銭だけに限りません。 私のコレクションから最高級の品も惜しみなく差し上げましょう。さて、件の男について話しましょう。 名はフランソワ・ゴンティエです\n私が追っていることを彼も承知しているので、足取りを隠すために自分のフリゲート艦を売却しました。同業者によれば、 彼はパナマで目撃されたそうです。捜索はそこから始めるのがよいでしょう。";
			link.l1 = "では、これで失礼します。";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "それでは幸運を祈ります。このゴンティエは非常に経験豊富な船乗りで、無謀な悪党どもを従えています。 彼には失うものが何もないので、死に物狂いで戦ってくるでしょう。";
			link.l1 = "ああいう奴なんか怖くないが、言われたことは考えておく。\nさらばだ、安心しろ。たとえ地獄でも必ず奴を捕まえてやる。";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "素晴らしい！これであいつはクラゲに報告書でも書けるってわけだ。俺に逆らう奴なんていやしねえ。感謝するぜ、 "+pchar.name+"、あなたは欠かせない人物です。";
			link.l1 = "ありがとうございます。 "+npchar.name+"、私の行動に対するそのような高い評価をいただきありがとうございます。さて、報酬の方はいかがでしょうか？";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "もちろんです。そのような困難な仕事には正当な報酬をお支払いしましょう。まずは、この優れた望遠鏡を差し上げます。 ";
			link.l1 = "「おったまげたぜ、なんて贈り物だ！」";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "さらに、こちらがあなたへの主な報酬として10万ペソ、そしてご自身の経費の補償として5万ペソでございます。";
			link.l1 = "「ありがとう」 "+npchar.name+"。改めて申し上げますが、あなたとお取引できるのは本当に光栄でございます。";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "いつも通り、一ヶ月後にお待ちしております。\n今回は大仕事でして、十分に装備を整えた艦隊が必要になります。\nその点をご理解いただき、しっかりとご準備ください。\nもし私の計画がうまくいけば、我々は大金持ちになれますよ。";
			link.l1 = "「よろしい」"+npchar.name+"……準備ができたら戻ってくる。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "残念だな、なんてことだ……まあ、落ち込むなよ、お前があのクズに騙された最初の男じゃないさ。いつか必ず奴を捕まえてやるさ\nさて、お前は一ヶ月後にまた来てくれ。今回は大仕事だから、装備も武装も整った艦隊を用意しておけ。 どうか本気で準備してくれ。俺の計画がうまくいけば、大金持ちになれるぞ。";
			link.l1 = "「よろしい」 "+npchar.name+"。準備ができたら戻ってくる。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "「ちょうどいい時に来たな、」 "+pchar.name+"！そろそろ心配し始めるところだった、君を探しに人を出そうと思っていたんだ\nさあ始めよう！今回の任務は本当に大きくて危険だが、報酬もそれに見合っている。 仕事が終われば百万ペソ以上を受け取れるぞ。";
			link.l1 = "「そうこなくっちゃ！話を聞こう。」 "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "奴隷となったインディオたちは小さな集団ごとに本土各地からハバナへ移送されていたし、 アフリカからもいくつかのガレオン船が到着して荷下ろしされた。\n今やハバナの要塞の高い壁の裏には、ほぼ五千人もの奴隷がいる。";
			link.l1 = "取引の内容はハバナへの強襲だという気がする。";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "「察しがいいですね」 "+pchar.name+"。まさにそれをあなたにお願いしたいのです。あなた以外には頼めません。 他のどの代理人にもこの任務は無理だと私は思っています\nお引き受けいただけますね？";
			link.l1 = "「正直に言うと、」 "+npchar.name+"、今は少し唖然としております。あなたの事業がこれほど大規模だとは存じませんでした。もちろん、 お引き受けいたします。 "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "「なあ、」 "+npchar.name+"、これはやりすぎだ。お前の奇襲にはもううんざりだぜ。次に欲深さを見せたら、 スペインに宣戦布告して俺一人で戦う羽目になるだろう。どうしても奴隷が必要なら、自分でハバナを襲撃しろよ。";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "お前がそんなことをするとは思わなかったぜ……くそっ、客に何て説明すりゃいいんだ？まあ、決めるのはお前だし、俺は新しい相棒を探すしかねえな。じゃあな、 "+pchar.name+"。今後もあなたのサービスは利用しませんぞ。七代先まで子孫を裕福にできたかもしれぬ取引を、 あなた自身が手放したことを覚えておきなさい。";
			link.l1 = "世界中の金をすべて手に入れることはできませんし、あなたは分不相応なことをしました。さようなら、 "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "同意してくれると思っていました。では、詳細をお聞きください。ハバナの要塞は昔から攻略が難しい標的でしたが、 今はさらに困難になっています。\nキューバの海岸には戦列艦が二隻警備しており、要塞を強襲する前にまずこの艦隊をどうにかしなければなりません……";
			link.l1 = "なるほど。戦列艦と戦うのはこれが初めてじゃねえさ、ははっ。俺に残された時間はどれくらいだ？";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "大した時間はありません。せいぜい三週間ほどで、その後奴隷たちはキューバのスペイン前哨地へ移送されます。 急がねばなりません。 ";
			link.l1 = "では、時間を無駄にせず行こう。俺はもう向かうぞ！";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "「少々お待ちを！」"+pchar.name+"、あなたと私の間にはこれまで誤解も不和も一切ありませんでした。それでも、 ここで何が起きているのかを知っておいていただきたいのです。私はあなたを信頼していますし、 依頼人は私を信頼しています\nこの事業には多大な労力と資金を投じております。奴隷一人残らず、 五千人全員を私に引き渡していただかねばなりません\nさもなくば、あなたに対して非常に厳しい措置を取らざるを得なくなります。気を悪くなさらずに、 これはあくまで警告です。 ";
			link.l1 = "「心配するな、」 "+npchar.name+"、商売というものは理解しておりますので、品をお渡しした際には必ずお支払いくださいますようお忘れなく。それでは、 失礼いたします。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "さて……それで、あなたの勝利の褒賞はどうなりますか？";
				link.l1 = "私には "+sTemp+" 奴隷たち。";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "ほうほう。私が言ったことを忘れたのですか？私に五千人以上の奴隷を連れてくる約束でしたが、 あなたが持ってきたのは "+sTemp+"。なぜですか？";
				link.l1 = "ふむ……ハバナからの旅で何人かは生き残れなかった……食料も薬も底をつきかけていたのだ。";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "ほうほう……俺を騙そうってのか？俺が言ったことを忘れたのか？俺の奴隷たちはどこだ、聞いてるんだぞ！どこにいるんだ！？";
			link.l1 = "うむ……その、ですね……";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "よろしい。説明など要らん。取引は成立している、一週間やるから五千人以上の奴隷を集めろ。 さもなくば大変なことになるぞ。";
			link.l1 = "わかった、わかった、落ち着けよ、俺が取ってきてやるからな。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "素晴らしい！今回もいつも通り私の依頼を見事に果たしてくれましたね。あなたにはとても満足しています。";
			link.l1 = "私も同じ気持ちです……ですが、積荷の代金を受け取れば、さらに嬉しいでしょう。";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "それは大変嬉しく思います。遅れてはいましたが、私の依頼を実に見事に果たしてくれました。";
			link.l1 = "さて、今度は積荷の代金を受け取りたいのです。";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "かしこまりました。私は奴隷を顧客に売りますので、彼が支払い、あなたは報酬を受け取ることになります。 前回と同じ流れです。さて、今回はあなたがここに連れてきたのは\n "+sTemp+" 奴隷。その金額は "+FindRussianMoneyString(iSlaveMoney)+"。1週間後に支払いを受け取りに来てください。";
			link.l1 = "「結構です」 "+npchar.name+"、取引成立だ。一週間後にここへ来る。だが、くれぐれも用心してくれ……";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+"、どうか、やめてください。私たちはパートナーであり、互いに不正や不信の余地はありません。 私はあなたにたくさんの金貨を約束し、あなたはそれを受け取っています。面白い仕事も約束し、それも果たしました。 私の商売が最も苦しい時でさえ、あなたの出費は必ず補償してきました。私が約束を破ったことが一度でもありましたか？ ";
			link.l1 = "ふむ……いや……俺はただ報酬が欲しいだけだ、それだけさ。";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "「さて……」"+pchar.name+"、あなたは私の最良の代理人ですし、今後もまたお取引できることを期待しております。 ";
			link.l1 = "「結構です」 "+npchar.name+"。しかし、私の立場もご理解いただきたいのです――百万ペソは莫大な金額でございます。";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "よく理解しておりますが、まず奴隷を売却しなければなりません。その後で初めて代金を受け取ることができます。";
			link.l1 = "よろしい。お互い理解し合えたようですね。";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "素晴らしい。では一週間後にお会いしましょう。さて、これから準備して取引先のもとへ向かわねばなりません。";
			link.l1 = "それではお邪魔しません。また一週間後にお会いしましょう。 "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "私はここで何をしているのかって？まあ……ここは私の銀行です。二日前に買いました。あなたが私の最初のお客様でして、 とても魅力的な融資条件をご提案できますよ……";
			link.l1 = "「くそったれな借用証なんてどうでもいい！どこに」 "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "落ち着いてください！彼はずっと前に逃げました。";
			link.l1 = "どうやって？";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "知らないのか？彼は一週間前に姿を消したんだ。どうやら顧客全員の投資を持ち逃げしたらしい。 総督ですら被害にあったそうだ。この家は置き去りにされていて、私が植民地から買い取ったんだ。";
			link.l1 = "消えた？どうやって？";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "彼が我々の植民地から逃げ出したと聞いております……あなたにも借金があるのでしょうか。しかも多額に？";
			link.l1 = "百万人以上だと！？だが、このネズミは必ず仕留めてやる！どこへ行きやがった？奴の船の名前は？";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "誰にも分かりません。本当に。彼はただ姿を消したのです。その日、「モーリシャス」か「モールディウス」 という名の船が出航しましたが、もしかすると彼はそれを使って逃げたのかもしれません。";
			link.l1 = "くそっ！あの野郎を信用した俺がバカだった！最初の日から裏切り者の臭いがしてたじゃねえか！それなのに、 俺たちは本当の仲間だなんて思い込んじまったとはな！だが、あいつにはいつか必ず後悔させてやる……いいだろう、"+npchar.name+"…私の振る舞いをお詫びいたします。もしあなたが立派な方であれば、今後はぜひお取引させていただきますので、 ご安心ください。ですが今は、これで失礼いたします。";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "問題ありません。承知いたしました。もしお金が必要でしたら、あるいは投資をご希望でしたら、 いつでも私がご用意いたします。";
			link.l1 = "ありがとう。しかし、自分の金は自分で持っていた方がよさそうだ。またな。";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "ほう、そうか？どうやら本人は俺と話したくないようだな……まあいい、お前と話を進めようじゃねえか。 "+pchar.GenQuest.Noblelombard.Name+" 私に借りがある "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" そして私の利息も―― "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" 三か月間だ。もし明日までに金を見せなければ、あいつの遺品は売り払うつもりだ。 その品があいつにとってどんな価値があろうと、私には関係ない。商売は商売だからな。";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "素晴らしい！それなら、私はすぐに全額と利子をまとめてお支払いしましょう―― "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+"。彼自身で遺物を受け取るでしょう。これがあなたのお金です。";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "私の依頼人は三ヶ月後に金を用意します。取引をしましょう、過去三ヶ月分とこれから三ヶ月分の利息をお支払いします。 "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+"。そして借金そのものは後ほどお支払いします。";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "私の顧客は三か月後に資金を用意できます。\nここ三か月分の利息をお支払いしますので、顧客が十分なお金を用意できるまでお待ちいただけませんか？";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "この珍品はとんでもない値段ですぞ！どうやら私の依頼人自身が支払うことになりそうですな。";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "素晴らしい！すべてうまくいった、金も手に入れたし "+pchar.GenQuest.Noblelombard.Name+" 彼は遺物を取り戻すことになる。";
			link.l1 = "お取引できて光栄です "+npchar.name+"！それでは、しばしのお別れです。";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "ふむ……よかろう。これで構わん。だが、もし "+pchar.GenQuest.Noblelombard.Name+" 三か月以内に金を用意できなければ、これ以上の猶予は認めません。そのことを必ず彼に伝えてください。";
				link.l1 = "承知しました！取引が成立して嬉しいです。それでは、さようなら。";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "いいえ。無理です。日没までに全額が必要です。その「依頼人」に必ず伝えてください。 これ以上お話しすることはありません。";
				link.l1 = "ふむ……よろしいでしょう。妥協する気がないのは残念です。";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "ふむ……よろしいでしょう。あなたの依頼人への敬意からのみ受け入れます。しかし、もし "+pchar.GenQuest.Noblelombard.Name+" 三か月以内に金を用意できなければ、これ以上の猶予は与えません。そのことを必ず彼に伝えてください。";
				link.l1 = "もちろんです！取引が成立して嬉しいですよ。それでは、さようなら。";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "いいえ。無理です。日没までに全額が必要です。その「依頼人」に必ず伝えてください。 これ以上お話しすることはありません。";
				link.l1 = "ふむ……よろしいでしょう。残念ですが、妥協する気はないのですね。";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "それは驚きだな！ "+pchar.GenQuest.Noblelombard.Name+" あなた名義の預金は開設しておりません。彼は我々の植民地にもいません――ヨーロッパへ航海して行きました。申し上げますが、あんな不誠実な男は見たことがありません。 私を騙そうとしましたが失敗しました――私にもいくつか手がありますので……";
				link.l1 = "この野郎！あいつは俺に約束したんだ……";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "「その通りです。」 "+pchar.GenQuest.Noblelombard.Name+" あなたの名義で預金がされています。どうぞ、お受け取りください…";
				link.l1 = "素晴らしい！では、ごきげんよう。 "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "そのようなものは、あのような者たちには存在しない "+pchar.GenQuest.Noblelombard.Name+" やつらには名誉も良心もないからです。あなたもあいつに騙されたのでしょうか？";
			link.l1 = "彼はそうしたんだろうな。まあ、どうでもいいが。 "+npchar.name+"、私もここに長く留まるつもりはありませんし、ヨーロッパは狭いものです……いつかどこかで会うかもしれませんね。さらば！";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "旦那、私はあなたを存じ上げません。私は地元の市民か船長にしか金を貸しませんので、悪しからず……";
			link.l1 = "なるほど。残念ですね。";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "な、なんだと……どういう意味だ？";
			link.l1 = "てめえはクソ野郎のネズミだな！よく聞け、俺はそんなに馬鹿じゃねえ。ピネットは手紙を二通書いたんだ。 お前に渡したのはその一通、もう一通は俺が信頼してる手下が持ってる。\nもし俺に何かあったら――その手紙は俺の手下が総督の手に直接届けるぜ……";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "だから、俺の健康を毎朝のミサで教会に祈ってくれよ、刺客を送り込む代わりにな。\n最後の警告だ！俺に手を出したら、ただじゃ済まねえぞ。\nわかったか？よし。深呼吸してドゥブロン銀貨でも数えてな。";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "お前と話す気はない。";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "もちろんでございます！多くの方はただ金を受け取ってすぐに立ち去りたがります。特に最近の噂を考えますと……";
			link.l1 = "「どんな噂だ？」";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "乗組員たちの状況が悪化しているそうです。ブラックウッド旦那でさえ、 最近は損失が常態化しても容認するようになりました――以前は決してなかったことです。しかし、それは私の関知するところではありません。私はただ商品を売るだけです。\nそれで、何にご興味がありますか？";
			link.l1 = "本題に入りましょう。";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}

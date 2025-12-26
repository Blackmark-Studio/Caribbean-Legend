#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("First Tavern Visit " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴り響いていて、みんながお前を探している。俺だったら、ここにはいないぜ。","街の衛兵たち全員が町中を探し回ってお前を捜しているんだ。俺は馬鹿じゃねえし、お前とは話さないぞ！","「走れ」 "+GetSexPhrase("相棒","娘")+"……兵士たちにミンチにされる前にな……"),LinkRandPhrase("何の用だ、 "+GetSexPhrase("ろくでなし","くせえ野郎")+"？！町の衛兵がお前の匂いを嗅ぎつけた、もう遠くへは行けねえぞ"+GetSexPhrase("「この汚い海賊め！」","")+"","殺人者め、今すぐ俺の所から出て行け！衛兵！","俺はお前なんか怖くねえぞ。 "+GetSexPhrase("悪党","ネズミ")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には全然問題ねえよ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("黙れ "+GetWorkTypeOfMan(npchar,"")+"、さもないと舌を引き抜いてやるぞ！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"「そしてそこにいる全員が―海賊を捕まえるためさ！だから言うんだ、相棒よ：おとなしくしてりゃ死なずに済むぜ…」"));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("「てめえか、この野郎！ここでラムを飲ませてやると思ってんのか？そんなわけねえだろ！\nおい、野郎ども！武器を取れ！このクズをぶっ殺せ！」","飲みたいのか、海賊？はっ！冗談じゃねえ！今からお前に思い知らせてやるぜ！野郎ども、刃物を抜け！");
				link.l1 = RandPhraseSimple("え？何だって？","止まれ！");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "旦那、仕事を探しているんだ。何か仕事はあるか？";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "任務は完了したぜ。ラム酒を積んだロングボートはル・フランソワ湾に届けて、お前さんの仲間に引き渡した。";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "何かご用ですか、旦那？";
				Link.l1 = "やあ、酒場の親父、俺の船のために乗組員を雇いたいんだ。手伝ってくれるか？";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "またお会いしましたね。今回は何のご用ですか、旦那？";
				Link.l1 = ""+npchar.name+"、邪魔してるのは分かってるが、あと一つだけ質問させてくれ。航海士が必要なんだが、 どこで見つけられるか心当たりはあるか？";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "何の用だ、旦那？";
				Link.l1 = "いくつか質問に答えてもらえると期待していたんだ。";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "部屋を借りたいんだ。";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "お会いできて光栄です、旦那！\nご用件は何でしょうか？ラム酒、ブランデー、スコッチウイスキーはいかがですか？";
				Link.l1 = "一番上等なフランス産ワインを一本と部屋の鍵を頼む。";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "すでにお支払いいただいております、旦那。お部屋は二階でございます。";
				Link.l1 = "「ありがとう。」";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "どうなさいますか、船長？あんなことがあった後ですから、一杯飲みたくなるでしょう。";
				Link.l1 = "それは後でいい。実は、起きたことについて話したいんだ。";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "「失礼しました」 "+GetAddress_Form(NPChar)+"、だが今日は一滴の酒も出せねえんだ。";
				Link.l1 = "何だと？どんな酒場がラム酒の一滴すら出せねえんだ？俺が知らねえうちに、全部飲み干すような大宴会でもあったのか？ ";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("俺のささやかな酒場へようこそ『"+XI_ConvertString(NPChar.City+"TavernName")+"「、旦那。お会いできて嬉しいです。」","お任せください、旦那！当店の酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「新しい訪問者をいつでも歓迎しております。」","ここは初めてですか、旦那？どうぞご遠慮なく、こちら『"+XI_ConvertString(NPChar.City+"TavernName")+"「いつも自分の家のようにくつろげるんだ！」"),LinkRandPhrase("お入りください、船長旦那。あなたのことは存じ上げませんので、ここ『』にいらっしゃるのは初めてですね\n"+XI_ConvertString(NPChar.City+"TavernName")+"「。」","今まで会ったことはありませんな、旦那。自己紹介しましょう。私は "+GetFullName(npchar)+"、「『"+XI_ConvertString(NPChar.City+"TavernName")+"「。」","新しいお客様をお迎えできて嬉しいです、キャプテン旦那！私の酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「最初の一杯はいつもサービスだぜ！この店の主人は俺だ、 "+GetFullName(npchar)+"、あなたを歓迎する。"),LinkRandPhrase("旦那船長！酒場『へようこそ\n"+XI_ConvertString(NPChar.City+"TavernName")+"「！」","おお、なんと輝かしいイダルゴ様が我らの酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「！ここは初めてですか、旦那？」","おはようございます、旦那！私は "+GetFullName(npchar)+"「『」の謙虚な店主"+XI_ConvertString(NPChar.City+"TavernName")+"「」、ここへお迎えできて嬉しいです！"),LinkRandPhrase("こんにちは、旦那船長。私は酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「。初めてのご宿泊ですか？」","ごきげんよう、旦那。酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「。」","お会いできて嬉しいですぞ、旦那船長！我々自慢の酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「」がご挨拶申し上げます！ラム酒、ワイン、それともお誘いしてよろしければ、いたずら好きな新しいオランダの酒、 ジンはいかがです？"));
				Link.l1 = LinkRandPhrase("ここは居心地がいいな……自己紹介させてもらおう―― "+GetFullName(pchar)+"、お会いできて光栄です。",""+GetFullName(pchar)+"、お会いできて光栄です。さて、俺に何を提供してくれるんだ？","私の名前は "+GetFullName(pchar)+" 俺はこの港に来たばかりだ。この酒場は何で有名なんだ？");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "おう、ルンバ！旅から戻ったのか、それとも新しい航海に出るところか？";
					link.l1 = "こんにちは。 "+npchar.name+"。ちょっと立ち寄っただけだ。";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "それで、船長、俺に持ってきてくれたのか "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "ああ、持っているぜ。ほら、これだ……";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "いいえ、まだだ……";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "ご用件は何ですか、旦那 "+GetSexPhrase("旦那","ご婦人")+"?";
						link.l1 = "あそこのテーブルにいる俺の友達にラム酒を一本頼む。";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("おお、名誉あるお客様方！おい、そこのお前――どけよ、勇敢な船長様の席を空けろ！さっさとしろ、さもないとぶん投げるぞ、ははは！","天の慈悲深き神よ！これは "+GetFullName(pchar)+"！最高級のワインが新しく入荷したばかりです、どうぞお入りください！","「ああ、」 "+GetAddress_Form(NPChar)+"、お困りですか？治療させてください。このボトルはサービスです。信じてください、 これはこの辺りで一番のワインですよ……"),LinkRandPhrase("おお、船長じゃないか "+GetFullName(pchar)+"「おい、そこのお前！立派な船長に敬意を払え！ここは納屋じゃねえんだぞ！船長、失礼しました。 こいつらの母親は礼儀を教えなかったみたいで。」","「ほう、ほう、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！今夜は長くなりそうだな、はは！お嬢さんたち、一番いいドレスを着ておいたほうがいいぞ！","「こんにちは。」 "+GetFullName(pchar)+"、お会いできて嬉しいです！どうか、旦那、お願いがあります。新しいテーブルを買ったばかりなので、 今夜は喧嘩はご遠慮ください。"),LinkRandPhrase("こんにちは、船長。どうぞごゆっくり。ただし、 うちの店ではあのシャープ船長でさえ礼儀を守ることを忘れないってことを覚えておいてくれよ。","おおっと！誰が来たかと思えば！それは "+GetFullName(pchar)+" 本人登場か！お前がいない間、ちょうど退屈し始めてたところだぜ！俺が新しいラム酒の樽を開けるから、 その間に仲間たちに冒険話でも聞かせてくれよ、船長！","おおっと！これは "+GetFullName(pchar)+" 自分自身だよ！またあんたの大冒険話でうちの客を海に連れ出すつもりじゃないだろうな？")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"！この老いぼれ船乗りは、あんたが店に来てくれるといつだって嬉しいんだ！どうぞ旦那、席にお掛けください、 女の子たちが世話をしますよ！","どうぞ、船長、くつろいでください！いつでも大好きなお客様をお迎えできて嬉しいです。 お好みのお酒は何になさいますか？","また会えて嬉しいよ。 "+GetFullName(pchar)+"！お席をご希望ですか？それともカウンターに座りますか？"),LinkRandPhrase("こんにちは、船長。空気が冷えてきましたね、今作ったばかりの極上のホットワインをどうぞ、ご馳走しますよ！","やあ、船長 "+GetFullName(pchar)+"！また来てくれて嬉しいよ。何が欲しいんだい？","あなたがいてくれて嬉しいよ "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！うちのささやかな店をごひいきにしてくれて嬉しいぜ！お客さんに喜んでもらえるように全力を尽くしてるんだ。"),LinkRandPhrase("船長！ようこそ、ようこそ！ルイ王にふさわしい見事なダンジュワインがあるんだ、 しかもあんたのために特別に取っておいたんだぜ！",""+GetFullName(pchar)+"！来てくれて本当に嬉しいよ。こいつら海のネズミどもを追い払おうか？それとも残しておく方がいいかい？任せてくれ、 あんたのためなら酒場ごと全部きれいにしてやるぜ！","なんてこった、船長が来たぞ "+GetFullName(pchar)+"「おい、色男ども――一番上等なテーブルクロスを船長の卓に持ってこい！」")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("ほう、俺のことを覚えてくれていたのか……おい、相棒、グラスを満たしてくれ、周りを見てくるからな……","落ち着けよ、相棒。今日は機嫌がいいんだ。まずはラム酒から始めようぜ、どうだ？…"),RandPhraseSimple("あら……私がここにいるのがそんなに嬉しくないのかしら？聞き間違いだといいんだけど、ふふ！","おい。お前の挨拶よりワインの方がうまいといいがな。そうじゃねえと、俺も怒っちまうかもしれねえぞ……")),RandPhraseSimple(RandPhraseSimple("いつもお前に会いに来るのは嬉しいぜ、相棒。塩気のきいた野郎を温めるもんは何かあるか？","ああ、あなたの店は日を追うごとに良くなっていくな！ここに来るのはいつも楽しみだよ…"),RandPhraseSimple("年老いた放浪者のことを忘れていなかったのか？嬉しいぜ、友よ。","また古い友に会えて嬉しいぜ……まだラム酒は残ってるか？")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("聞いているぞ、船長。","俺の酒場『"+XI_ConvertString(NPChar.City+"TavernName")+"「お仕えします、船長！」","耳をかたむけてるぜ、船長！今日は何をご所望だ？");
				Link.l1 = "この島に海で運試しをしたい若い奴らはいるか？";
				Link.l1.go = "crew hire";
				Link.l2 = "いくつか質問に答えてもらえると期待していたんだ。";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "財政の件について話したい。";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("最近教会で起きた盗難について何か知っているか？","最近教会で起きた強盗事件について何か知っているか？","最近教会で起きた強盗事件について何か聞いたか？");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "この植民地であんたは何でも知ってるって噂だ。俺は買いたいんだ "+pchar.GenQuest.Device.Shipyarder.Type+"、それがあなたの町で売られたと聞いたんだ。さて、誰かが露店でそれを売っていたらしい。 何か知っていることはあるか？";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "「名前が」 "+pchar.GenQuest.Sunplace.Trader.Enemyname+"。どこで彼に会えるんだ？";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "「こんにちは」 "+npchar.name+"……ジェイコブ・ファン・ベルクを探さなきゃいけないんだが、どこにいる？お前の酒場には見当たらないんだが……";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "「こんにちは」 "+npchar.name+"。フェルナンド・ロドリゲスという名のカバジェロを探しているんだ。あんたの町に現れたか？";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "俺の取り分を受け取りに来たぜ。ちゃんと預かってくれてただろうな。 "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "「という名の男がどこにいるか探していたんだ」 "+pchar.GenQuest.Marginpassenger.q2Name+"？あいつはあなたの町に住んでいる。";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("タダで部屋を貸してくれるのか、相棒？","空いている部屋はありますか？しばらくここに滞在したいのですが。");
					link.l3.go = "room";
				}
				Link.l4 = "「残念だが、もう出発するところだ」 "+NPChar.name+"。では、また。";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "ああ、まあ、入ってくれ、入ってくれ。ここはいつでも歓迎だぜ。";
			link.l1 = "はい、ありがとうございます。お会いできてよかったです。では、ごきげんよう。";
			link.l1.go = "exit";
			Link.l2 = "新しい手が欲しいんだ。ちゃんと使える奴らを頼むぜ、いいな？";
			Link.l2.go = "crew hire";
			link.l3 = "しっかりした陸地で休んで考えをまとめたいけど、母さんが家の中をせわしなく動き回っている間は無理だな。";
			link.l3.go = "Helen_room";
			Link.l4 = "ちょっとお尋ねしてもいいか？ ";
			Link.l4.go = "quests";
			link.l5 = " 「お前と話したいことがあるんだ」 "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "ご用件は何でしょうか、ご親切な方 "+GetSexPhrase("旦那","ご婦人")+"?";
				link.l1 = "あそこのテーブルにいる俺の仲間にラム酒を一本持ってきてくれ。";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("聞いているぞ、船長。","「何をお望みですか、船長？」","それで、船長、どうするんだ？");
			Link.l1 = "「乗組員が必要だ」 "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+"……話をしようじゃねえか……";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "財政の件について話し合いたい。";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("最近教会で起きた盗難について何か知っていることはあるか？","最近教会で起きた強盗について何か知っているか？","最近教会で起きた強盗事件について何か聞いたか？");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "この植民地であんたが何でも知ってるって噂だ。俺は買いたいんだ "+pchar.GenQuest.Device.Shipyarder.Type+"、そしてそれがあなたの町で売られていたと聞きました。さて、誰かが通りでそれを売っていたのです。 そのことについて何かご存知ですか？";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "「名前が付いた悪徳業者について教えてくれ」 "+pchar.GenQuest.Sunplace.Trader.Enemyname+"。どこで彼に会える？";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "「こんにちは」 "+npchar.name+"……ヤーコブ・ファン・ベルクを探さなきゃいけないんだが、どこにいる？お前の酒場には見当たらないんだが……";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "「こんにちは」 "+npchar.name+"。フェルナンド・ロドリゲスという名のカバジェロを探しているんだ。彼はあなたの町に到着したか？";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "俺の取り分を受け取りに来たぜ。お前がちゃんと預かってくれてるやつだ。 "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "「という名の男がどこにいるか探していたんだ」 "+pchar.GenQuest.Marginpassenger.q2Name+"？あいつはあなたの町に住んでいる。";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("「ただで部屋を貸してくれるのか、相棒？」","空いている部屋はありますか？しばらくここに滞在したいのですが。");
				link.l3.go = "room";
			}
			Link.l4 = "後でまた来るとしよう。";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "「それで船員が何のために必要なんだ、船長？港にお前の船は見当たらねえぞ。」";
				link.l1 = RandPhraseSimple("まったくだ……俺は間違った場所に停泊してしまったんだ。","港に入るのを忘れちまった……");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "普段なら船乗り志望の男たちが大勢いるんだが、今はもう遅いぜ。朝になれば奴らが現れ始めるさ。\n部屋を借りて待ってみるかい？";
				link.l1 = "わかった。空いている部屋はあるか？";
				link.l1.go = "room";
				link.l2 = "今は部屋には興味がない。またな。";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "ここが指名手配犯のたまり場だと思ってるのか？衛兵を呼ばないだけ感謝しな。";
					link.l1 = "ありがとう。";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "船長、今日は酒場に誰一人いませんぜ。行く気のある奴はみんなブラックウッド船長について行っちまいました。";
						link.l1 = "それは残念だな！";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "ああ、すまねえ船長、ちょっと遅かったな。船乗り志望の連中はみんな、 ついさっき腕利きの船長と一緒に出航しちまったぜ\n "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "それは残念だな！";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "船長、あんたはケチだって噂だぜ。ここにはあんたの船に乗りたい奴なんていねえよ。";
									link.l1 = "なるほど……";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "聞く耳を持っているぜ。";
			//link.l1 = "仕事を探しているんだ。手伝ってくれないか？";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("最近のニュースを教えてくれないか？","この地で何が起きているんだ？","陸では何か新しいことがあったか？");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "俺は別の用事で来たんだ。";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "どこで見つけられるか知っているか "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "どこで探せばいいか教えてくれるか "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "おう、あんたの息子に呼ばれて来たんだ。"; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "それで、見たか  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "どこを探せばいいか教えてくれないか  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "巡回隊の船長がどこにいるか知っているか "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "それで、見たか "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "巡回隊の船長について何か知っているか "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "「という男がどこにいるか教えてくれないか "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "ここからそう遠くない場所で、たまたま船の書類を見つけたんだ……";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "聞いてくれ、俺は昔の友人を探してるんだ。 "+pchar.GenQuest.FindFugitive.Name+" が彼の名前だ。仲間の船長が、彼はお前さんの居留地に向かっていると言っていたぜ。ひょっとして会ったことがあるか？ ";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "何もありません、ありがとう。";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("「何だと？」 "+pchar.GenQuest.Hold_GenQuest.Name+"「？ふむ……聞いたことがねえな。」","本当に彼は我々の町の出身なのか？そんな人物は聞いたことがないぞ。","うちの小さな植民地にはそんな奴はいなかったぜ。ここにいる間、一度もそいつのことなんて聞いたことねえな。");
					link.l1 = "本当に確かか？";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "見てみろ "+pchar.GenQuest.Hold_GenQuest.foundStr+"、彼はそこによくいるんだ。";
					link.l1 = "ありがとうございます、そうさせてもらいます。";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("「何だと？」 "+pchar.GenQuest.Hold_GenQuest.Name+"？ふむ……聞いたことがないな。本当にうちの村の者なのか？そんな人は聞いたことがないぞ。","へっへっ……まあ、今となっちゃあ、あいつがどこにいるかは神様しか知らねえな――地獄か天国か。もう一年以上前にくたばったってのによ、まだあいつのことを聞いてくる奴がいる……可哀想に、あの野郎も安らげねえな……"),RandPhraseSimple("そこにはいないぞ――少なくとも生者の世界にはな。彼はつい最近亡くなったんだ……黄熱病でな……神の御許で安らかに眠れ……あいつは昔は本当に頑丈な男だった！若い頃は大冒険家だったんだぜ！だが死神が迎えに来たら、もうどうしようもねえ……","おや、あの人が恋しいのかい？もうずっと前にこの辺りを去ったよ。どこへ行ったか誰にも分からない――北アメリカの植民地かもしれないし、ヨーロッパに戻ったのかもしれない。荷物をまとめて、さっさといなくなったんだ。 "),"「ああ、それを探しているのか」 "+pchar.GenQuest.Hold_GenQuest.Name+" ニューイングランドで金持ちになって自分の家を買った奴のことか？あいつにな、 昔はラム酒をツケで売ってやったもんだ――今でもまだ借りがあるんだぜ。人間ってのは本当に恩知らずだよな。");
					link.l1 = "なるほど。まあ、とにかくありがとう。";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "さて、酒場以外のどこであいつを探すんだ？あいつは常連でな、酒で罪を流してるんだよ、へっへっ。 少し時間を置いてまた来な。もし現れたら、お前を待つように伝えてやるさ。";	
					link.l1 = "ありがとうございます、そうします。";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "ここにいる全員を個人的に知っているのに、どうして確信が持てないんだ。 ここで酒場を経営してもう何年にもなるんだぞ。 "+"俺はあいつらをあらゆる状態で見てきたぜ。時には女房が旦那を迎えに来ることもあったし、 時には自分で帰るやつもいた。たまには俺が放り出さなきゃならねえこともあったんだ。「本当にかって？」 もちろんだとも！";
			link.l1 = "まあ、とにかくありがとうな……";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("彼はここによく来るが、今はここにいないんだ。\n時々また来てくれ――もし彼が現れたら、君を待つように伝えておくぜ。","彼はここによく来る常連だ。後でまた来れば、きっとここで会えるぞ。","時々戻ってきてくれ——あいつはここによく来るからな。お前が探していたことを伝えておくぜ。");
			link.l1 = "ありがとうございます、また後で戻ってきます……";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "もうここに来ているから、どこかその辺にいるはずだ…";
			link.l1 = "ありがとう。";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "あいつを知らねえ奴なんているか？ここ数日、入植地中の連中がずっとあいつの話でもちきりだぜ。";
			link.l1 = "もっと詳しく教えてくれないか？";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "少しだけな。船長は処刑されて、一部の乗組員も同じ運命を辿った。残りはカリブ中に散り散りになり、 地位も役職も奪われた……何のためだ？判事によれば、巡回中に海賊船を沈めて、その戦利品を自分のものにしたからだそうだ\n"+"こういうことだ、この船の持ち主も積み荷も見つかってねえ……地元の湾や入り江をくまなく探してるが、手がかりはまるでなしだ。";
			link.l1 = "「何だって、誰も隠し場所を白状しなかったのか？」";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "一人もいません！拷問されてもです！それでも、なぜ総督があんな中傷をあんなに簡単に信じたのか、 俺には未だに理解できません。船長 "+pchar.GenQuest.CaptainComission.Name+" 評判が良く、乗組員もよく訓練され規律正しかった。どんな提督でも羨むほどだった。";
			link.l1 = "「生き残った乗組員たちはどこで探せばいいんだ？」";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "それは分からねえな――奴らは四方八方に散っちまった……だがな……まだ一人だけ残ってるが、そいつから何か聞き出せるとは思えねえ。ひどい脳震盪を起こしてるんだ。知ってるか、 あいつは砲手として仕えてたんだぜ "+pchar.GenQuest.CaptainComission.Name+"。あの事故の二日後、彼は入り江で意識不明のまま発見された。最初は病院に送られ、英雄のように扱われたが、 事態が複雑になるにつれて地下牢に放り込まれ、尋問されそうになった。しかし結局、 まずは治療を受けさせるべきだと判断されたのだ。";
			link.l1 = "今もまだここにいるのか？";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "「ああ、」 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" 彼の名前だ。時々ここに現れては、物乞いで稼いだ小銭をラム酒に使ってしまうんだ。かわいそうな奴さ。 もし見かけたら、ここであなたを待つように伝えておくよ。";
			link.l1 = "ありがとうございます、また後で戻ってきます。";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "あいつを知ってるか？もちろん知ってるさ。で、あんたは何の用であいつを探してるんだ？";
			link.l1 = "俺はあいつに用があるんだ……";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+"、その「商売」には気をつけたほうがいいぞ。 "+pchar.GenQuest.CaptainComission.Name+" 海賊行為の疑いで拘留されていて、今や総督の手下たちが島中をくまなく捜索し、仲間を探しているんだ。";
			link.l1 = "そりゃ驚いたぜ！それで、そいつは何をしたんだ？";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "本当かどうかは分からねえが、通りかかった海賊船から押収した積荷を隠して提出しなかったって話だ。だが、 あの海賊も積荷も、いまだに誰にも見つかっちゃいねえ。それなのに、なぜ総督があんな中傷をあっさり信じちまうのか、 俺にはさっぱり分からねえよ。船長\n "+pchar.GenQuest.CaptainComission.CapName+"  評判も悪くなかったし、あいつは立派な兵士だった。俺の言葉を信じてくれよ。 "+GetAddress_Form(pchar)+".";
			link.l1 = "警告してくれてありがとな。じゃあな。";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "「それで、あんたは彼女を何に使うつもりだ？」";
			link.l1 = "俺はあの女に用があるんだ……";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "我々の入植地の男の半分は、あの女と何かしら関わりがあるようだ。もしうちの女たちがあいつを捕まえたら、 裸のまま町の門の外に放り出すだろうな。";
			link.l1 = "まあ、仕方ねえな…… "+GetSexPhrase("どうやら俺は長い列に加わったみたいだな。\nまあ、他にも彼女を探しに来る奴がいたら、俺の後ろに並ぶように伝えてくれ。","なるほど")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "ここにはよく来る常連だよ――たいてい仕事を探しに来るんだが、今はここにいないな。時々また来てくれ――もし彼が現れたら、君を待つように伝えておくよ。";
			link.l1 = "ありがとうございます、また後で戻ってきます……";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "「おや、そうか、君が」 "+GetSexPhrase("「連れてきたあの船長」","「連れてきたあの娘」")+" 「放蕩息子が若い花嫁を連れてきたのか？」";
				link.l1 = "ああ、助けたのは俺だ。";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "おお、そちら "+GetSexPhrase("彼は、我々の恩人だ","彼女こそ、我々の恩人だ")+"。報酬を期待してるんだろう？";
				link.l1 = "「まあ、報酬なんてなくてもいいさ。あんたの感謝の言葉だけで十分だぜ。」";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "息子が困難な時に見捨てず、繊細な状況から抜け出す手助けをしてくださり、心より感謝いたします。\nどうか私からのささやかな金銭と贈り物をお受け取りいただき、改めてお礼申し上げます。";
			link.l1 = "ありがとうございます。この若いカップルを助けることができて嬉しかったです。";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感謝だと？何が感謝だ！？あの間抜けが仕事もせずにぶらぶらしてもう半年だぞ――それなのに浮気する暇はあるんだとよ！俺があいつの年の頃にはもう自分の商売を切り盛りしてたってのに！ふん！ 総督には嫁入り前の娘がいるってのに、あの馬鹿は身寄りもない女をうちに連れてきて、 よくもまあ祝福してくれなんて言えたもんだ！";
			link.l1 = "一目惚れなんて信じてないんだろう？";
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
			dialog.text = "愛？愛だと！？俺をからかってるのか、それとも馬鹿なのか？若い者の気まぐれに付き合って、 まるで女衒みたいな真似をしおって恥を知れ！娘を家から連れ出しただけじゃなく、 俺の息子の人生まで台無しにしたんだ。お前に感謝なんてするものか。さようなら。";
			link.l1 = "それならお前にも同じことを返すぜ。";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "見せてくれ！ふむ……だが、お前は自分自身が船長じゃねえか。この件は港長に相談した方がいいと思うぜ。";
				link.l1 = "助言ありがとうございます。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "見せてくれ！おお！この名前を見る限り、これは私の常連客の一人の物だな、かなり立派な紳士だよ。 私が直接この書類を持ち主に渡せる。私に渡してくれるか？";
				link.l1 = "考え直してみると……";
				link.l1.go = "exit";
				link.l2 = "持っていけ。役に立てて嬉しいぜ。";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("俺は誰に仕えるかなんて気にしねえ、金に国籍はねえからな。だが、お前には協力しねえぞ、お前が来たのは の旗の下だからな。 "+NationNameGenitive(sti(pchar.nation))+".","俺はただの酒場の主人だが、協力して "+NationNameAblative(sti(pchar.nation))+" 俺には魅力的じゃねえな。");
				link.l1 = RandPhraseSimple("まあ、好きにしな…","まあ、好きにしな…");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("ここには普段から多くの乗客がいるんだがな。\nそれでも、お前の船で旅をしようなんて考える間抜けは一人もいないだろうよ。\nお前の悪名はすでに知れ渡ってるぜ。そんな悪党と一緒に航海するのは、よっぽどの馬鹿だけだ。","商人たちから護衛の依頼を受けることはよくあるんだが、あんたの悪名はすでに広まっている。 だから誰にもあんたを勧めるつもりはない。自分の評判も大事なんでね。誰だって羊の番に狼を雇いたくはないだろう。");
				link.l1 = RandPhraseSimple("ああ、本当に、そんな噂話を全部信じちゃいけないよ……","なるほどな。みんなを黙らせるのは難しいもんだぜ。","最近の人間はまったく甘ちゃんだな……");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "「で、お前の船はどこだ？それとも乗客を背負って泳ぐつもりか？」";
				link.l1 = "おい、確かに一理あるな……";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "もし海賊の居留地や敵国の港に行くのが怖くないなら、仕事を紹介できるかもしれねえぜ。\n何か特別に探してるものでもあるのか？";
			link.l1 = "それは問題ないだろう。護衛をつけてもいいぜ。";
			link.l1.go = "work_1";
			link.l2 = "乗客はいるか？金さえ払えば、どこへでも連れていってやるぜ。";
			link.l2.go = "work_2";
			link.l3 = "いいえ、そんな仕事は俺には向いてない。ありがとう。";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "通常、俺には護衛任務の依頼は来ねえんだ。酒場にいる商人たちに聞いてみな――もしかしたらお前の助けを必要としてるかもしれねえぞ。";
				link.l1 = "「わかった、あなたの言う通りだ。」";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "申し訳ありませんが、あなたと一緒に旅をしたがる者はおりません。";
					link.l1 = "なるほど。";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "今入ってきた男がいる――さっき通りかかった船について尋ねていたぜ。話してみたけりゃ、声をかけてみな。";
					link.l1 = RandPhraseSimple("あいつは誰だ？もしかして悪党か？それとも、もっと悪い、指名手配中の海賊か？","「そいつは誰だ？そいつと揉め事になるようなことはあるのか？」");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "いいや、今日は誰もそれについて尋ねてこなかった。\nもしかしたら、また別の日にでもな。";
					link.l1 = RandPhraseSimple("まあ、そこにないなら、仕方ねえな……","俺の運の悪さよ……まあいい、じゃあな。");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "今日は誰もいないぜ。二、三日後にまた来な。";
				link.l1 = "「わかった、あなたの言う通りだ。」";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("誰が知ってるんだ？聞かれたから答えただけさ。","さて、これはお前が解決することだ。そこにいる誰のことも俺は保証しねえぞ。","いろんな奴がここに来るぜ。ここは酒場だ、船長。総督の屋敷じゃねえんだ。");
			Link.l1 = "ありがとう、じゃあ交渉しよう。";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("誰が知ってるんだ？聞かれたから答えただけさ。","さて、これはお前が解決することだぜ。俺はあそこにいる誰にも保証はしねえぞ。","いろんな奴がここに来るぜ。ここは酒場だ、船長、総督の屋敷じゃねえんだ。");
			Link.l1 = "なるほどな。この男が何者か、調べてみよう…";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "もちろんだよ、ヘレン。どれくらい滞在するんだい？それに、何だ、グラディス婆さんと喧嘩でもしたのか？";
			if(!isDay())
			{
				link.l1 = "朝までただ眠るだけだ。今帰ったら、きっと彼女を起こしてしまう。";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "いやいや、ただ夜に出航したいだけで、彼女を起こしたくないんだ。";
				link.l1.go = "Helen_room_night";
				link.l2 = "ゆっくり長く眠って、のんびり起きたいんだ。今日は部屋を借りるぜ。";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "「部屋は使用中だ」 "+GetAddress_Form(NPChar)+"、俺にはどうすることもできねえ。";
				link.l1 = "「そうか、残念だな……」";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "アンリ・ティボー旦那が現在部屋を借りておりまして、しかも一ヶ月分前払いしておりますので、船長、 私にはどうすることもできません。";
				link.l1 = "「そうか、残念だな……」";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "「部屋は使用中だ」 "+GetAddress_Form(NPChar)+"、俺にはどうすることもできねえ。";
				link.l1 = "「そうか、残念だな……」";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "「部屋は使用中だ」 "+GetAddress_Form(NPChar)+"、俺にはどうにもできねえんだ。";
				link.l1 = "「まあ、それは残念だな……」";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "残念ですが、いいえ、船長。すべての部屋はブラックウッドとその手下たちが占領しています。";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "「ああ、なんて残念なんだ！」";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "全部の部屋？ここには部屋が複数あるのか？";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "部屋を借りたいのか？問題ねえ。100エイト払えば使っていいぜ。";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "「ほら、金だ。」";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "ふむ……また後で戻ってくるとしよう……";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "部屋はあんたのものだ。どうぞ入ってくつろいでくれ。";
				link.l1 = "ありがとな、相棒。";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "部屋を借りたいのか？問題ねえ。100エイトであんたのもんだ。";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "ほら、金だ。";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "ふむ……また後で来るとしよう……";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "部屋はあんたのものだ。中に入ってくつろいでくれ。";
					link.l1 = "ありがとな、相棒。";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "失礼します、船長、あいにく部屋は空いておりません。あの客が出ていかないのです。それに、 まだ支払いもしてくれなくて……";
				link.l1 = "どうやら今夜は大部屋で過ごすしかなさそうだな……";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "すまねえ。他の話をしようぜ。";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "じゃあ、衛兵を呼べよ。なんだこの客は？金も払わねえし、出て行く気もねえ……";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "ここにどれくらい滞在するつもりだ？";
			if(!isDay())
			{
				link.l1 = "朝まで。";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "夜まで。";
				link.l1.go = "room_night";
				link.l2 = "次の朝まで。";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.MarySexBlock"))
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "部屋はご自由にお使いください、船長。まったく無料です。";
				link.l1 = "ありがとな、相棒。";
				link.l1.go = "room_day_wait";
				link.l3 = "今はやめておこう。他の話をしよう。";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "それは8レアル銀貨5枚かかるぜ。";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "取引成立だ。ほら、受け取れ。";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("その値段で？王族の部屋でも借りるつもりか？俺はただで大部屋に泊まる方がましだぜ。","ああ、どうやら今の俺にはベッドで寝る贅沢なんて手が届かねえようだな。仕方ねえ、広間のベンチで寝るしかねえか。");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "今は違う。話題を変えよう。";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "部屋はご自由にお使いください、船長。まったく無料です。";
				link.l1 = "ありがとな、相棒。";
				link.l1.go = "room_day_wait_next";
				link.l3 = "今はやめておこう。他の話をしよう。";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "それは8レアル銀貨10枚かかるぜ。";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "取引成立だ。ほら、受け取れ。";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("その値段で？王族の部屋でも借りるつもりか？俺はむしろ無料の大広間に泊まるぜ。","ああ、今の俺にはベッドで寝る贅沢なんて叶わないみたいだな。\n仕方ねえ、広間のベンチで寝るしかなさそうだ。");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "今は違う。話題を変えよう。";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "部屋はご自由にお使いください、船長。まったく無料です。";
				link.l1 = "「ありがとな、相棒。」";
				link.l1.go = "room_night_wait";
				link.l3 = "今はやめておこう。他の話をしよう。";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "それは8レアル銀貨5枚かかるぜ。";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "取引成立だ。ほら、受け取れ。";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("その値段で？王族の部屋でも借りるつもりか？俺はむしろ無料の大広間で寝るぜ。","残念ながら、今の私にはベッドで眠る贅沢は手が届かないようですな。仕方ない、広間のベンチで寝るしかないか。");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "今は違う。話題を変えよう。";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "さっさと出ていけ、このろくでなしめ！大広間は無料だが、まともな振る舞いは期待してるんだぞ！";
				link.l1 = "わかった、わかった、もう行くよ。";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "さっさと出て行け、このろくでなしめ！大広間は無料だが、まともな振る舞いを期待してるんだぞ！";
				link.l1 = "わかった、わかった、もう行くよ。";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "今すぐ私の酒場でのその無礼な振る舞いをやめなさい、さもないと衛兵を呼びますよ！";
			link.l1 = "わかった、わかった、もう行くよ。";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "俺はあまり詳しくねえ……常連客に聞いたほうがいいぜ。";
			link.l1 = "なるほど、ありがとうございます。";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "「掛け売りはしていません」 "+GetSexPhrase("旦那","お嬢さん")+".";
			link.l1 = "俺はちゃんとした金貨で払ってるぜ。もう金や銀は受け取らねえのか？";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "申し訳ありません。 "+GetSexPhrase("旦那","お嬢さん")+" 船長、でもあんたの友達には借金があって、俺はてっきり……";
			link.l1 = "あれこれ考えずに、もっと手を早く動かせ。さて、俺の勇敢な友がいくら借りてるんだ？";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+"、お嬢さん"+GetSexPhrase("ター","ｓ")+" 船長、それにあいつは教会の本も何冊か質に入れていた――持ち物はそれだけで、多少は価値があったんだ。";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "ほら、これが約束の金貨だ。写本を渡せ。気をつけて扱えよ――これは卑猥な絵本なんかじゃなくて、聖なる聖書なんだからな！";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "少し待ってくれ……金を持って戻るぜ";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+"、お嬢さん"+GetSexPhrase("ター","ｓ")+" 船長。";
				link.l1 = "俺があいつの借金を返して、担保に残した物は全部もらうぜ。";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "いいえ、お嬢さん"+GetSexPhrase("ター","ｓ")+"、それじゃうまくいかねえよ。";
			link.l1 = "「“そうはいかねえ”ってどういう意味だ？船長の借金は返した――あいつは問題なし。お前も金を取り戻した――お前も問題なし。俺があいつの担保を受け取った――俺も問題なし。みんな問題ねえ――なのに、なんで“そうはいかねえ”なんだ？」";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "だって、お嬢さん"+GetSexPhrase("ター","ｓ")+" 船長、俺は金なんていらねえよ。あの船長のことはよく知ってるから、返済されるとも、 この写本を引き取ってもらえるとも最初から思っちゃいなかったさ。";
			link.l1 = "金はいらないだと？最初からこの本を自分のものにするつもりだったのか？だが一体なぜだ、神に誓って！？";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "神の御名において――まさにその通り、だからこそだ、お嬢さん"+GetSexPhrase("ター","ｓ")+"。私の小さな息子がとても重い病気にかかり、妻と私は、 もし祝福された主が子供の熱を治してくださったら教会に寄付をすると誓いました。主の慈悲は尽きることなく、 息子は元気に生きています。だから今、私たちは誓いを果たさなければなりません。そしてちょうどその時です、船長 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 現れてこれらの教会の本を質に入れようとしたんだ。神の言葉で酒代を払うなんて不敬極まりない――だから私はこれらの本を我々の教区の牧師に渡すことにしたんだ。";
			link.l1 = "まあ、確かにこれは善行だが、実はこの本は別の神父――いや、ただの神父ではなく司教であり、私の霊的な導き手のものなんだ。彼は怒るかもしれんし、 教会の財産を盗んで寄付した者には呪いをかけるかもしれんぞ。だから、私が君からこれらを買い取り、 無事に持ち帰りたい。君はそのお金を自分の教区に寄付すればいい。きっと神も同じように喜ばれるはずだ。";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+GetSexPhrase("ター","ｓ")+"…お嬢さん"+GetSexPhrase("ター","ｓ")+" 船長……もちろん、私は全く知りませんでした！すぐにお返ししますし、見返りのお金も一切要りません。 どうか司教様に私たちのことを一言伝えてください――できれば祝福していただき、この誓いから解放してもらえれば……";
			link.l1 = "もちろん、あなたの誓いは守られたと見なされるさ！結局のところ、 本を正当な持ち主に返すために自分の利益を手放したんだからな。どの教会かなんて関係ないさ、神は唯一、 聖なるカトリック使徒教会もひとつだけだろ？\nよし、それじゃ本を渡してくれ、幸運を祈るぜ…";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "ふむ、 "+pchar.GenQuest.Device.Shipyarder.Type+"？今まで聞いたことがねえな……それは一体なんだ？俺の知る限り、そんなものは聞いたことがねえぞ。";
			link.l1 = "「まあ、これは船大工の道具だ」 "+pchar.GenQuest.Device.Shipyarder.Describe+"。そんなものを誰かがお前に持ちかけたのか？";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "ふむ……ああ、確かに変わった奴がその品を持ってきたな。だが、あれが何かは教えてくれなかった――ただ酒と交換しようとしただけさ。もちろん断ったぜ――そんなガラクタはいらねえからな。";
				link.l1 = "「そいつはどんな奴だったんだ？それにどこへ行った？俺はその道具がどうしても必要なんだ。」";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "いや、そんなことはない。悪いが、力になれねえ。周りの連中に聞いてみな。";
				link.l1 = "なるほど。さて、聞き込みを始めるか！";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"？最近そこにいたが、今ごろは仲間の店主のところへ行ったはずだ。店で探してみな、きっとそこにいるはずだ。";
				link.l1 = "ありがとう！おかげで本当に助かったぜ！";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"？今朝早く、彼は自分のラガー船で航海に出たよ。きっと今ごろ舷側に立って景色を眺めてるだろうな。 彼に用があるなら、海で探すか、数日後に戻ってくるのを待つといいさ…";
				link.l1 = "ありがとう！待たずに海で探したほうが早そうだな。幸運を祈るぜ！";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "しーっ……なんでそんなに大声なんだ？あいつはずっと前からお前を待ってるぜ。ラム酒を一クォートも飲み干しちまった。 二階の部屋に行け、あいつはそこで待ってるぞ。";
			link.l1 = "ああ、なるほど。まだ起きていてくれるといいが。";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "はい、その旦那を知っていますよ。町のどこかにいるはずです――つい最近、私の窓の前を通り過ぎるのを見かけました。";
				link.l1 = "ありがとう！俺が探しに行くぜ！";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "ああ、その旦那なら知ってるぜ。町のどこかにいるはずだ――ついさっき、俺の窓の前を歩いていくのを見たからな。";
					link.l1 = "ありがとう！俺があいつを探しに行くぜ！";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "はい、彼は今うちの町を訪れているよ。今はここにいない――自分のブリガンティンで出航したんだ。きっとこの島の周辺の海域、そう遠くないところにいるはずだ。\n";
					link.l1 = "助かったぜ、相棒！お前のおかげで本当に助かった！";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "フェルナンド・ロドリゲス？聞いたことねえな。いや、この男については何も知らねえよ。";
				link.l1 = "なるほどな……まあ、捜索は続くぜ……";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "はい、もちろんです。おめでとうございます、船長。すでにあなたの勝利は聞いております。これがあなたのお金です。";
			link.l1 = "ありがとうございます。 "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "「ええっと、旦那、」 "+pchar.GenQuest.Marginpassenger.q2Name+" およそ亡くなった "+LinkRandPhrase("一ヶ月","三週間","二ヶ月")+" 前だ。 "+LinkRandPhrase("突然熱病で倒れた","町の門で刺されたんだ――盗賊か、あの赤い肌の野蛮人どもかもしれねえ","決闘で撃たれた")+"……神の御許で安らかに……";
				link.l1 = "くそっ…！それで、あいつの…まあ、いいさ。情報ありがとう。またな、 "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"？ああ、町のどこかにいるはずだ。通りで探してみな。ただし、毎日正午までは総督の執務室にいるし、 夜九時を過ぎると自分の家に閉じこもるから気をつけろよ。";
				link.l1 = "ありがとう！探しに行ってくる…";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("どうやらお前の船長は本当のことを言っていたようだな。 "+pchar.GenQuest.FindFugitive.Name+" 確かに最近我々の居留地に到着したばかりだ。昼間は通りで探してみな、たいてい暇そうにぶらぶらしているからな。","その男についてはもう聞かれたし、知っていることは全部話しただろう！","ふざけてんのか、それとも本当にバカなのか！？同じことをもう三回も聞いてるじゃねえか！","考えただけで、どうしてあんな馬鹿が船長になれたんだ……","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("助かったぜ、相棒！お前のおかげで本当に助かった！","「ああ、ああ、わかったよ。」","おったまげたぜ、そんなに興奮すんなよ。ちょっと忘れてただけだ。","まあ、見ての通り、あいつはやったんだよ……",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("いや、相棒、その名前は聞いたことねえな。周りに聞いてみな、誰か知ってるかもしれねえぞ…","その男についてはもう聞かれたし、俺は言っただろう、知らねえって！","ふざけてるのか、それとも本当にバカなのか！？同じことをもう三回も聞いてるじゃねえか！","考えただけで、どうしてあんな間抜けが船長になれたんだ…","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("なるほど。まあ、とにかくありがとう。","ああ、ああ、わかったよ。","おいおい、そんなに興奮すんなよ。ちょっと忘れてただけだぜ。","まあ、見ての通り、奴はやったんだよ……",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "残念だが、今は力になれねえな。俺の知ってる連中は誰もあんたの下で働きたがらねえんだ。だが、ひとつ助言をやろう――ちょうどあんたのすぐ後ろの席に座ったあの水夫に話しかけてみな。あいつと仲間はついさっき商船を降りたばかりだ。 もしかしたら、あんたと一緒に行くことに同意するかもしれねえぜ。";
			link.l1 = "よし、そうするぜ！どうもありがとう！";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name = GetCharacterName("Alonso");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "具体的なことは何も言えねえな、友よ。今のところ、うちには航海士は来てねえんだ。\n港で聞き込みしてみな、もしかしたら誰かが何か知ってるかもしれねえぜ。";
			link.l1 = "なるほど。よし、俺が人々に話をしに行くぜ。";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "かしこまりました、旦那！…最高級のフランスワインでございます！ "+sld.name+"！一番いい客室を用意してこい！料金は1000ペソだ、旦那。";
			link.l1 = "「ほら。」";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "出て行け、このろくでなし！お前みたいな奴がいると、金を払う客の席がなくなるんだよ！";
				link.l1 = "わかったよ、もういい……俺は行くぜ。";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "ああ、でもな、うちの用心棒が客を酒場から引きずり出すなんてことになったら、他の客がビビっちまうだろ？それに、 兵隊がいるのを嫌がる客もいるんだよ。落ち着かなくなるってわけさ。俺の評判を落としたくねえんだ……";
				link.l1 = "ふむ、お前の問題を俺が解決したらどうだ？";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "決めたのか？あいつは武装してるし、どう見ても腕利きの傭兵だぞ…";
				link.l1 = "ふむ、確かにそうだな、武装した傭兵と口論する気にはなれねえ……";
				link.l1.go = "Exit";
				link.l2 = "俺だって修道院にこもった尼僧じゃねえよ……それでも部屋を借りたいんだ。";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "そうだな、もし君が、ええと……あいつをどかすことができるなら、その部屋は朝まで君のものだ。もちろん、料金はいただかないよ。";
				link.l1 = "なあ、やっぱり気が変わった。誰かを説得する気分じゃねえんだ。";
				link.l1.go = "Exit";
				link.l2 = "これは見逃せねえぜ。あんたの厄介な客が、でっけえカモメみてえに酒場から吹っ飛ばされるところだ。";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "なるほど。銀貨五枚だ。";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "もちろん、どうぞ。";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "実はな……やっぱりまた今度にしよう。今日は残りの時間を立って過ごすぜ。";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "賢明なご判断だ。銀貨五枚いただくぜ、おやすみ。";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "はい、どうぞ。そしてありがとう――おやすみなさい。";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "考え直したが、眠る気になれねえな。町をぶらついて、夜の空気でも吸ってくるぜ。";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "もちろんだよ、ヘレン。それで十ペソだ。";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "もちろん、どうぞ。";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "実は……丸一日あれば何か役に立つことができるんだが。まあ、また今度だな。";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "承知しました、ヘレン。";
			link.l1 = "うむ。";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "いい散歩をした後は、眠くなるかもしれないぞ。";
			link.l1 = "ははっ、そうかもな。";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "ご随意に。";
			link.l1 = "じゃあ、また今度な。";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "もちろんだ、ヘレン、聞く耳を持っているよ。";
			link.l1 = "町で最近のニュースや面白い噂は何かあるか？";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "奴は普段の三倍の値を払うんだ、だから……わかるだろう。しかも断るのはおすすめしないぜ――あいつは気難しい性格だからな。特に最近はな。";
			link.l1 = "「あいつ、どうしたんだ？」";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "執念だよ、それが原因さ。最初の頃は、あいつは気前が良くて親切な奴だった。船乗りたちは酒場で金をばらまき、 女の子たちに贈り物を買ってやってたもんさ。『レディ・ベス』が港に入ると、本当にお祭り騒ぎが始まったもんだ。\nでも今はどうだ？今じゃ食料しか買わねえし、手当たり次第に人を集めてる。まるで船乗りじゃなくて、 ただの労働力が欲しいみたいにな。まあ、自分で話してみるといいぜ。";
			link.l1 = "そうするかもな。ありがとう。";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

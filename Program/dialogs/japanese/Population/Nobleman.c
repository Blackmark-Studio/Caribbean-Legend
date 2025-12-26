//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("ふむ。お前は～の旗の下で航海しているのか "+NationNameGenitive(sti(pchar.nation))+"「おい、相棒。何しに俺たちの町に来やがったんだ？とっとと失せろ！」","「の仲間だと疑われたくはない」 "+NationNameAblative(sti(pchar.nation))+"「失せろ、さもないと衛兵に通報するぞ！」","逃げるならこれが最後のチャンスだ。\nさもなければ、自業自得になるぜ。","警告したはずだ。今度はその無礼の代償を払ってもらうぜ、この野郎！","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("そんな愛国者か、ええ！？","わかった、わかった、落ち着け。俺はもう行く。","あまり騒ぐな。俺は出ていくぞ。","何だって！？",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("見ろよ！それでいて、どうしてうちの衛兵どもはお前みたいなろくでなしを町中うろつかせてるんだ？ありえねえ……","消え失せろ、話す気もねえ！死刑執行人め……","逃げるならこれが最後のチャンスだ。\nさもないと、自業自得になるぜ。","警告したはずだ。今度はその無礼の代償を払ってもらうぜ、この野郎！","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("おいおい！もっと敬意を払えよ、旦那！","自分を見てみろよ、聖人様……","落ち着け……","「なんだって！？」",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。立派な船の船長だな。頼みたいことがあるんだ。引き受けるかどうかはお前次第だぜ。";
					link.l1 = "「聞いているぞ」 "+GetAddress_FormToNPC(NPChar)+"。どういう意味だ？";
					link.l1.go = "passenger";
					link.l2 = "「失礼します」 "+GetAddress_FormToNPC(NPChar)+"、しかし急いでいるんだ。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"。立派な船の船長でいらっしゃるのですね。お願いしたいことがございます。引き受けるかどうかはお任せします。";
					link.l1 = "聞いているぞ "+GetAddress_FormToNPC(NPChar)+"。どういう意味だ？";
					link.l1.go = "passenger";
					link.l2 = "「失礼します」 "+GetAddress_FormToNPC(NPChar)+"、しかし急いでいるんだ。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "ああ、我が町に紳士がお越しくださるとは嬉しい限りです！きっとヨーロッパからいらしたばかりでしょう。\n聞いていただきたいことがございます――紳士同士としてお願いしたいのです。どうか私の気持ちをお汲み取りいただければ幸いです。";
					link.l1 = "ごきげんよう、旦那。お話をうかがいます。";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "「ごきげんよう。」 "+GetAddress_Form(NPChar)+"！我が町の通りで紳士にお会いできるとは嬉しいことですわ！少しだけお時間をいただけますか？";
					link.l1 = "もちろん、旦那。お聞きします。";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "ごきげんよう、船長！お会いできて嬉しいです、あなたなら問題を解決できそうですから。";
					link.l1 = "問題によるな。俺は暴力で解決するのが得意だぜ。それがあんたの求めてることか、 "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("「こんにちは」 "+GetAddress_Form(NPChar)+"。俺に何か用か？","何の用だ、旦那？");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"。あまりお時間は取らせません、ちょっとお伺いしたいことがありまして…";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("お前の植民地について情報が必要だ。","情報が必要だ。");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("街中がピリピリしている――王室監察官のドン・フェルナンド・デ・アラミーダが到着したんだ。\nここでいろいろ見てきたが、これは……人を変えるのは悲しみそのものじゃなく、それにどう向き合うかなんだよ。\n彼は父親の死後、まるで別人になったって噂だ。今じゃ、この群島で彼ほど清廉潔白で……そして容赦ない王冠の忠臣はいないさ。","「『ホーリー・マーシー』を見てみろよ！王様自ら特別な設計で造らせたって話だぜ。それに見ろよ、傷一つねえ。 まるで聖母マリア様が守ってるみてえだ。だがな、噂も聞いたことがある……もしかしたら聖母じゃねえかもしれねえ。」\n","ドン・フェルナンドが何度命を狙われたか知っているか？公開海域で十二回も襲撃されたんだ――しかもそれは去年だけの話だ！\nだが、あれほど忠実で鍛え上げられた乗組員がいて、さらに主のご加護があれば、十三回目だってきっと生き延びるさ！"),LinkRandPhrase("聞いたかい？ドン・フェルナンド・デ・アラミダがうちの街に到着したんだってさ、 今まさにどこかの通りにいるらしいぜ。自分の目で一度見てみたいもんだな……","複雑な男だよ、このドン・フェルナンドは。母国の汚れを清める救世主だと言う者もいれば、父親の死で心が壊れ、 やがて俺たち全員が泣くことになると囁く者もいる。\nだが俺が言いたいのはこうだ――彼を恐れるな。彼をこうした連中こそ恐れろ。","なんてハンサムな男なの、あのドン・フェルナンド！でもね、不思議だと思わない？ まるで誰のことも目に入っていないみたい。義務と奉仕ばかりよ。女の子がいたって聞いたけど……ある神父と会ってからは、すっかり俗世の楽しみを断ったんだって。まるで誓いを立てたみたいにね。"),RandPhraseSimple(RandPhraseSimple("くそったれ検査官め！あいつがいる間は、街がまるで死んだようだ。商売もできねえし、楽しみもねえ。 息をするのさえ静かにしなきゃいけねえみたいだぜ。\nそして一番怖いのはな、どこの港でも同じってことだ。まるで機械仕掛けみてえによ。\n国王陛下が俺たち全員にこの拷問をわざと考え出したんじゃねえかって思うくらいだぜ！","ドン・フェルナンドがまた孤児院を訪れました。彼は惜しみなく寄付し、何時間も祈りを捧げています。 かくも立派な方こそ、あの呪われた横領者どもへの手本とすべきです！"),RandPhraseSimple("はっ！「聖人」フェルナンドがまた娼館を全部閉めちまったぜ。まあいいさ、あいつもすぐに出航するだろうし、 そしたらまたすぐに開くだろうよ。","検…検査官が来たんだよ、それが何だってんだ！ドン・フェルナンド・デ・アルメイダ、いや、なんだっけ、アルメイダだ！ あまりにも偉いから、総督でさえ彼の前じゃ気を遣うってさ。目を見ただけでお前の罪が全部見抜かれるらしいぜ。 怖いよな！")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("何だと？またか？私は君に構っている暇はない。他の話し相手を探しなさい。街には平民がたくさん歩いているだろう。\nそれに私は行かなくてはならない。今夜は総督邸で宴会があるから、衣装の準備をしなくては……","いや、もう本当にイライラするぜ！わからねえのか？それとも頭が鈍いのか？","旦那、あんたはただの馬鹿じゃなくて、田舎者で無礼者なんじゃねえかと疑い始めてるぜ。警告しておく、 俺に構うのはやめろ。さもないと後悔することになるぞ。","もういい。俺が教えてやるぞ、この無礼者め！","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("なるほど。さらばだ。","ああ、そうだ、何を聞きたかったか忘れちまったんだよ……","「私の言いたいことを誤解している……」","何だって！？",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("続けろ。","何の用だ？","質問か？よし、水夫、聞いてやるぜ。");
			link.l1 = LinkRandPhrase("あなたの町の最近の噂話を教えてくれないか？","最近ここで何か面白いことがあったか？","カリブ海から何か知らせはありますか、旦那？");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Sir","Madam")+"、植民地に行く必要がある"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"、できるだけ早く、それが始まる "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"、のため "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+"。あなたの船は、ここを航行している大半の小舟と比べて頑丈で速そうだ。あなたに報酬を支払える "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+"。どう答える？"; // belamour gen
			}
			else
			{
				dialog.text = "「こんにちは。」 "+GetSexPhrase("旦那","奥様")+"！俺はそこへ行かなくちゃならねえ "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"「！それは」 "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"、ところでな。ああ、ああ、わかってる――あの野郎どもが俺たちが現れるのを待ち構えてるってことはな。でも、どうしても外せねえ大事な用事があるんだ！ 俺はケチじゃねえ――払うのは好きじゃねえが、いつもちゃんと払ってる。今やってることは全部放り出してくれ、 着いたらすぐにお前にやるからよ\n "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "ふむ。俺もこの道を進むつもりだ、だからこの条件でお前を乗せてやるぜ。";
			link.l1.go = "passenger_1";
			link.l2 = "「申し訳ない」 "+GetAddress_FormToNPC(NPChar)+"、しかし俺は別の方向へ航海しているんだ。力になれねえよ。";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "残念だな。まあ、別の船を待つとするか。じゃあな。";
			link.l1 = "またな。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "よし！待つのはもううんざりだ。着いたら報酬を渡すからな。";
			link.l1 = "俺の船に行け。 "+GetAddress_FormToNPC(NPChar)+"。もうすぐ出発するぞ。";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
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
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "ここに着きましたな、まことに素晴らしい！あなたの船での旅はとても快適でした。規律ある乗組員と清潔な甲板、 感謝いたします。これがあなたのお金です、旦那。";
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
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "俺にはちょっと繊細な用事があってな……"+sTemp+" 今すぐ金が必要なんだ、でなきゃ本当にまずいことになる。\n普段なら他の紳士に金を頼むなんて絶対しないが、今回は本当に切羽詰まっているんだ。";
			link.l1 = "「いくら必要なんだ？」";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "金額はかなり少ない、つまり "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+"。で、俺を助けてくれるか？";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "ああ、もちろん。持っていけ。";
				link.l1.go = "donation_2";
			}
			link.l2 = "手伝いたいのは山々だが、俺の懐も空っぽなんだ――余分なペソなんて一枚もないぜ。";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "「感謝する」 "+GetAddress_Form(NPChar)+"！助けてくれてありがとう！総督邸に友人がいるから、あなたの寛大さを必ず伝えるよ。改めて千の感謝を！";
			link.l1 = "どういたしまして、旦那。あなたもきっと私に同じことをしてくれるでしょう。";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "助けが必要なんだ。あなたは裕福な紳士だから、きっと分かってくれると願っている。少し前、 私はどうしてもお金が必要で、銀行家のところへ行って質入れをしたんだ\n "+pchar.GenQuest.Noblelombard.Item+"\n彼は良い条件を提示してくれた。月利一割、合計三ヶ月だ。しかし、不運な出来事のせいで、 期限が来ても品物を買い戻す金がないんだ\n今になって、買い手が見つかったと言っている "+pchar.GenQuest.Noblelombard.Item+" もしすぐに借金と利子を返さなければ、あいつはそれを売ってしまうんだ。\nでも今はあまり金がないし、質に入れた品はとても貴重なものなんだ……";
			link.l1 = "「それについて、どうお手伝いすればよいですか」 "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "私の頼みは、うちの銀行家と話してくれということだ。金を渡すなり、俺の保証人になるなり……何か手を打ってくれ。残念ながら、他に頼れる者はいないんだ。親しい友人たちはみんな、急に“破産”してしまったからな。三か月後には\n "+pchar.GenQuest.Noblelombard.Text+"そして、かかった費用はすべて倍にしてお返しします！紳士の誓いです！";
			link.l1 = "よし、この件について手を貸してやるぜ。";
			link.l1.go = "lombard_2";
			link.l2 = "残念だが、今の俺は「破産」状態なんだ。だから助けてやれねえ、本当にすまねえ！";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "ご理解いただきありがとうございます。\n酒場でお待ちしています。\nできるだけ早く来てください。";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard.id = npchar.id;
			AddDialogExitQuestFunction("Noblelombard_TookQuest");
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "何か言いたいことがあるのか、 "+GetAddress_Form(NPChar)+"？銀行に行ってきたのか？いい知らせか、それとも悪い知らせか？";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "ああ、返したぞ。お前の借金は全部俺が肩代わりした。あそこへ行って遺品を取り戻してこい。";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "はい。過去三か月分の利息も、これから三か月分の利息もすべて返済しました。安心してお金を待っていてください。 ただし、三か月後には元金を忘れずに返済してくださいよ。";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "あります。過去三ヶ月分の利息はすべて返済しました。銀行家は、 あなたが全額を用意するまでさらに三ヶ月待つことに同意しました。";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "「何か言いたいことがあるのか、」 "+GetAddress_Form(NPChar)+"？銀行に行ってきたのか？いい知らせか、それとも悪い知らせか？";
				link.l1 = "あるさ。あの守銭奴がとんでもない額を要求してきたんだ。譲歩の申し出も全部断られて、必要な金も持っていない。 だから助けてやれなかったんだ。すまない。";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "「何か言いたいことがあるのか」 "+GetAddress_Form(NPChar)+"？銀行に行ってきたのか？いい知らせか、それとも悪い知らせか？";
				link.l1 = "任せとけ。待ってろ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "「ふん」 "+GetAddress_Form(NPChar)+"…今やあなたも、あの忌々しい血に飢えた高利貸どもの抑えきれぬ強欲の証人となったわけだ。神に誓って、旦那、 あいつらはユダヤ人も顔負けだぜ！俺みたいに金を借りようとする時は、そのことを忘れるなよ。 少なくとも努力してくれてありがとう…";
			link.l1 = "あいつらは昔から好きじゃねえ。まあ、高利貸しなんて誰が好きなんだ？悪いな、 "+GetAddress_FormToNPC(NPChar)+"。さらばだ。";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_fail");
		break;
		
		case "lombard_5":
			dialog.text = "信じられない！君が私を助けてくれたんだ、 "+GetAddress_Form(NPChar)+"！この恩は決して忘れません。あなたの費用はすべて倍にしてお返しすることをお約束します。三か月後に我々 の銀行家のもとへお越しください。あなた名義で預金口座を開設いたします。";
			link.l1 = "わかったよ、言う通りにするぜ。またな！";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "改めてありがとう、船長。幸運を祈るぜ！";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_success");
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "俺は～を持ってる "+LinkRandPhrase("工場","俺のもの","プランテーション")+" それに、俺はいつだって新しい奴隷が必要なんだ。この気候じゃ、すぐに奴らがやられちまうからな。今はちょうど "+sti(npchar.quest.slaves.qty)+" 首だ。俺はその首をまとめて注文したい。首一つにつき金貨で払うぞ。 "+sti(npchar.quest.slaves.price)+" ドゥブロン金貨\n急ぐ必要はねえ、俺が欲しいものを手に入れてくれりゃ時間の制限はしねえ。ただし、常識の範囲でな、 半年以上も引き延ばすんじゃねえぞ。どうだ？やるか？";
			link.l1 = "取引成立だ！奴隷売買は汚い商売だが、リスクを冒す価値はあるぜ。";
			link.l1.go = "slaves_1";
			link.l2 = "失礼だが、俺は奴隷商人じゃねえ。そんな仕事はやってないんだ。";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "よろしい。それでは、貨物を持ってきた時にお待ちしています。私は毎日午前11時から午後1時まで教会におります。残りの時間は忙しいか仕事中です。";
			link.l1 = "わかった。覚えておくぜ。またな、 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "持ってきたか "+sti(npchar.quest.slaves.qty)+" 俺が頼んだ奴隷たちはどうしたんだ、船長？";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "ああ。全部の荷は俺の貨物室にあるぜ。いつでも引き渡す準備はできてる。";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "いや、俺がやる。";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "船長、もし奴隷の件で来たのなら……もう十分買い取ったから、今はこれ以上必要ないんだ。来るのが遅すぎたな、すまない。";
				link.l1 = "残念だな！でも君の言う通り、俺の動きが遅かった。じゃあな！";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "素晴らしい。すぐに彼らのためにロングボートを出そう。";
			link.l1 = "俺の報酬はどうなってるんだ？";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "心配するな、覚えてるぜ。ほら、この金を受け取れ。 "+sti(npchar.quest.slaves.price)+" 1人あたりドゥブロン金貨だ。お互いにとっていい取引だろう、そうだよな？";
			link.l1 = "ありがとう。あなたと取引できて楽しかったよ。";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "そうだな……失礼するぜ、もう行かなくちゃ。じゃあな！";
			link.l1 = "「幸運を祈るぜ」 "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、この町の市民として、剣を納めてくれ。","聞いてくれ、この町の市民として頼む、剣を納めてくれ。");
			link.l1 = LinkRandPhrase("「よし。」","承知した。","「よし。」");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}

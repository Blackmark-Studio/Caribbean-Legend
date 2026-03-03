//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "ごきげんよう、息子よ。貧しい者たち、あなたの魂、そして聖母教会のために、どうかご慈悲を示し、 銀貨をいくらか寄付していただけませんか。";
					link.l1 = "そうですね、神父様、キリストとその教会が教えてくださるように、私たちは皆で助け合わねばならないのでしょう。\nそのお金がどこへ行くのか教えていただけますか？";
					link.l1.go = "donation";
					link.l2 = "申し訳ありません、神父様、でも今の私は教会のネズミほど貧しいんです。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "ごきげんよう、息子よ。頼みごとがあるのだ。もちろん報酬は払うぞ。";
					link.l1 = "お話を伺います、神父様。ご用件は何でしょうか？";
					link.l1.go = "passenger";
					link.l2 = "申し訳ありません、お父様、でも行かなければなりません。";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "ごきげんよう、息子よ。君は船長だとお見受けする。そこで君に提案があるのだ。";
					link.l1 = "お聞きします、神父様。";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("ごきげんよう、息子よ。どうしたのだ？","ごきげんよう、息子よ。告解したいなら神父のところへ行きなさい。","ごきげんよう、息子よ。「若き日にあなたの創造主を覚えよ。」"),LinkRandPhrase("ごきげんよう、息子よ。どうしたのだ？","ごきげんよう、息子よ、神のご加護がありますように！","ごきげんよう、息子よ、神の御加護がありますように！"));
				link.l1 = LinkRandPhrase("「あなたも同じく、神父様。ご機嫌いかがですか？」","ごきげんよう、神父様。ご教区の様子はいかがですか？","「ご機嫌いかがですか、お父さん？」");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("「お尋ねしたいことがあります、神父様。」","情報が必要だ。");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "神父様、私の船には人々が乗っています。彼らは奴隷で、キリスト教徒もいれば、洗礼を受けていない異教徒もいます。 異教徒には洗礼を授け、キリスト教徒には聖体拝領をお願いします。その後、 私は彼ら全員を神と我らの教会の栄光のために解放します。";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "神父様、私の船に祝福を授け、乗組員のためにミサを捧げていただきたいのです。費用はいくらかかりますか？";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("失礼します、神父様、でも私は行かなくてはなりません。","ご迷惑をおかけして申し訳ありません、神父様。","父上、俺は自分の船に戻らなきゃならない。さらばだ！");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("またお前か、わしの子よ？何の用じゃ？","「他に何か話したいことがあるかい、息子よ？」","また会えて嬉しいぞ、息子よ。");
				link.l1 = LinkRandPhrase("「そちらこそ、お父さま。ご機嫌いかがですか？」","ごきげんよう、神父様。ご教区の様子はいかがですか？","「ご機嫌いかがですか、お父さん？」");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("「お尋ねしたいことがあります、神父様。」","情報が必要だ。");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "神父様、私の船には人々がいます。彼らは奴隷で、キリスト教徒もいれば、洗礼を受けていない異教徒もいます。 異教徒たちには洗礼を授け、キリスト教徒たちには聖体拝領をお願いします。その後、 私は彼ら全員を神と我らの教会の栄光のために解放します。";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "神父様、私の船に祝福を授け、乗組員のためにミサを捧げていただきたいのです。費用はいくらかかりますか？";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("失礼します、神父様、でも私は行かねばなりません。","ご迷惑をおかけして申し訳ありません、神父様。","父上、俺は自分の船に行かねばなりません。では、さらば！");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "お前に急ぎの用件がある、息子よ。この書類をあの教区の牧師に届けてほしい。  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+"……そちらへ航海するのか？書類は二週間以内に届けなければならん……";
				link.l1 = "簡単なことですよ、神父様。その書類を渡してください、私が届けます。 "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "喜んでやりたいんですが、神父様、俺は別の方向へ航海しているんです。";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "息子よ、急ぎの用件で私を助けてくれないか？我々の教会では聖書と祈祷書が不足しており、必要とするすべての人々 に配っているのだ\n最寄りの植民地まで航海してくれないか "+NationNameGenitive(sti(npchar.nation))+"、地元の教会から聖書や祈祷書をいくつか受け取って、ここに持ってきてくれませんか？ そしてできれば一ヶ月以内にお願いします。残りがあまりありませんので。";
				link.l1 = "喜んであなたの教会を手伝うよ。これらの本はどの牧師からでも手に入るのか？";
				link.l1.go = "Churchbooks";
				link.l2 = "喜んでやりたいんだが、神父様、今はできねえんだ。";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("大丈夫だ、息子よ。ご親切な言葉をありがとう。","私たちの教区は元気ですよ、息子よ。ご心配いただきありがとうございます。");
			link.l1 = "それでは、失礼します、神父様。";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "もちろんだ、息子よ。 "+sTemp+"";
			link.l1 = "「どれくらいの寄付が十分と見なされますか？」";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "すべてはあなたの財布とご意志次第ですよ、息子よ。「神は喜んで施す者を愛される。」 どんなご寄付でも心より感謝いたします。";
			link.l1 = "１００ペソ";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000ペソ";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000ペソ";
			link.l3.go = "donation_rate_3";
			link.l4 = "１万ペソ";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "コインをありがとう、我が子よ！善き目的のために使わせてもらうぞ！";
				link.l1 = "どういたしまして、神父様。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "「欺かれてはならぬ、神は侮られることはない。人は自分が蒔いたものを、必ず刈り取るのだ。 肉に蒔く者は肉から滅びを刈り取り、霊に蒔く者は霊から永遠の命を刈り取るのである。」";
				link.l1 = "ハハッ！説教なんていらねえ、俺は施しなんざしねえんだ。とっとと失せな！";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "感謝する、息子よ。この金額は本当に我々の教区の使命の助けになる。神のご加護を！";
				link.l1 = "「ご武運を、神父様！」";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "「神の報いが貴様を待っておるぞ、若造め！キリストの聖なる教会の僕を嘲るとは、なんたる冒涜だ！」";
				link.l1 = "ははっ！俺は施しなんてしねえ。とっとと失せな！";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "こんなにも寛大だとは思いもしませんでしたよ、息子よ！次の手紙で司教様にあなたのことをお伝えしますし、 毎日あなたのために祈ります！あなたに祝福を授け、感謝してお金を受け取ります！";
				link.l1 = "金は神の御心のために使われなければ無意味です！幸運を祈ります、神父様！";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "「神の報いが貴様を待っておるぞ、若造め！キリストの聖なる教会の僕を嘲るとは、冒涜じゃ！」";
				link.l1 = "ハハッ！俺は慈善なんかしねえ。とっとと失せな！";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "なんと……今、私の耳を疑いましたぞ？本当に一万ペソも寄付してくださるのですか！？あなたに祝福を、 そしてありがたくお金を受け取ります。次の司教宛ての手紙であなたのことを必ず書き記し、毎日お祈りいたします！ これは教会にとって大きな助けです！";
				link.l1 = "「多く与えられし者には多く求められる」、そうでしょう？幸運を祈ります、神父様。";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "神の報いが貴様を待っているぞ、野郎！キリスト聖教会のしもべを嘲るとは、冒涜だ！";
				link.l1 = "ハハッ！俺は慈善なんかしねえ。とっとと失せな！";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "もちろんだ、息子よ。我々の聖なる務めは、この哀れで惨めな人々を助けることだ。君の頼み、引き受けよう。";
			link.l1 = "ありがとうございます、神父様。洗礼と聖餐を受けた囚人一人につき、8レアル銀貨を10枚寄付いたします。";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "必要ではありませんが、ありがたく盗まれた報酬を受け取ります。あなたのお金は我々の教区の様々 な任務に使わせていただきます。\nあなたの船まで案内していただけますか？";
			link.l1 = "はい、お父さん。ついてきてください。";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "それはお前の艦隊全体の船の数とその大きさ次第だぜ。";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "金がかかるぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+"、息子よ。";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "この金額をお支払いできます、神父様。お受け取りください。";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "残念ながら、そんなに多くのお金は持っていないんだ。";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "よろしい、息子よ。聖なる器を集めてから港へ行こう。";
			link.l1 = "「ついてきてください、お父上。」";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "こんにちは船長、自己紹介させていただきます。私は神父でして、軍艦の従軍司祭としてかなりの経験があります。 前の船を離れたのは、船長と私の間に…道徳的な意見の相違があったからです。私をあなたの乗組員に加えてみませんか？";
			link.l1 = "神父が乗ってるのか？教えてくれよ、神父さん、船の司祭って何をするんだ？";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "なぜなら、それはまったく明白なことです。私はあなたとあなたの乗組員のために神に祈り、毎日ミサを行い、 戦いの前にはあなたの部下たちに祝福を与え、告解を聞きます。神の言葉はあなたの乗組員の手と心に力を授けます。 乗組員たちは定期的に聖体拝領と告解を受ける機会を得られるでしょう。信じてください、恩寵の状態にある水夫は、 不信心者がひるむような状況でもしっかりと踏みとどまるのです。\n私自身に多くは求めません――私の故郷の教区のための五万ペソの一時金、船室の簡素な寝台、そして士官たちと同じ食事。それだけで十分です。";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "面白い……その通りだ、良い船長は船員の体だけでなく魂のことも気にかけねばならん。ようこそ乗船された、神父！";
				link.l1.go = "capellan_2";
			}
			link.l2 = "いいえ、神父様。申し訳ありませんが、あなたのご奉仕を頼む余裕はありません。";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "信頼してくれてありがとう、息子よ。お前は賢く金を使ったな。しかし警告しておくぞ、私は立派な船長にしか仕えん。 商人でも私掠船でも構わんが、海賊船では絶対に説教はしない！\nもしお前が悪魔のジョリーロジャーを掲げることがあれば、私は最初の港で即座に船を降りるぞ。";
			link.l1 = "そのことは考えておくよ、神父。がっかりさせないように頑張るぜ。さあ、船に乗り込んで、乗組員に自己紹介してくれ！ ";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
		
		case "capellan_4":
			dialog.text = "何か必要かい、息子よ？";
			link.l1 = "いいえ、なんでもありません、お父様。";
			link.l1.go = "exit";
			link.l2 = "神父、次の港で船を降りていただきたい。これ以上の説明はしない。";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "よろしい、息子よ。ここはお前に任せる。次の居住地でお前の船を降りよう。";
			link.l1 = "ご理解いただきありがとうございます、神父様。";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "なんてことだ、船長！私がもし海賊旗を掲げたらあなたのもとを去ると警告したはずです！ 次の港であなたの船を降ります。あなたがすぐに悔い改め、聖母教会のもとに戻られるよう祈ります。";
			link.l1 = "ちくしょう……";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "My "+GetSexPhrase("息子","娘")+"、俺は～に行かなくちゃならねえ "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" 始まった "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"、のために "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+"。支払うぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" そのことで。どう思う？";
			}
			else
			{
				dialog.text = "My "+GetSexPhrase("息子","娘")+"、主は神秘的な方法でお導きになります。だからこそ、私は信頼できる船長を探しているのです。私を"+目的地+"まで連れて行っていただけますか "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+"、それは～にある "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"？敵は決して眠らないから、まるで灼熱のゲヘナへの旅のようだというのは分かっている。 君がイエス・キリストじゃないのも分かっているが、俺も使徒じゃないから、多少の蓄えはある。さて\n "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" お前に十分か？";
			}
			link.l1 = "「同意します、神父。」";
			link.l1.go = "passenger_1";
			link.l2 = "申し訳ありません、お父様。でも私は別の方向へ航海しています。お力にはなれません。";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "それはすべて神の御心だ、息子よ。私は別の船を待つことにしよう。神の平安があなたと共にあらんことを！";
			link.l1 = "「ごきげんよう、神父。」";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "神のご加護を！目的地に着いたら報酬を渡すぞ。";
			link.l1 = "俺の船に向かってくれ、父さん。すぐに出航するぞ。";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
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
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "ありがとう、私の "+GetSexPhrase("息子","娘")+"。約束を守ってくれたな、今度は俺の番だ。約束通り、金を受け取れ。";
			link.l1 = "ありがとうございます。ご武運を、神父様。";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
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
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "ここだ。これを持っていきなさい、息子よ。覚えておきなさい、届けるまで二週間しかないぞ。牧師が待っている。 行きなさい、神のご加護がありますように！";
			link.l1 = "ご期待には必ず応えます、お父様。では、ごきげんよう。";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "ああ。どの植民地でも手に入るぞ "+NationNameGenitive(sti(npchar.nation))+"。見つけた本はすべて教会の牧師のところへ持っていってくれ。神のご加護がありますように！";
			link.l1 = "ありがとうございます！すぐに本をお渡しします。";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}

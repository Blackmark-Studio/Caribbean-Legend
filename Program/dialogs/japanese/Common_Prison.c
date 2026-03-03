// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

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
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("俺は看守だ。ここで何の用だ？","何の用だ？なぜ牢屋に来たんだ？");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "マッカーサー嬢？お会いできるとは驚きました。私の知る限り、 あなたの乗組員やスウェンソン船長の部下は誰も逮捕していませんよ。";
				link.l1 = "俺はここにいただけだ、旦那。いけねえのか？あんたの背後で囚人たちと話してたわけじゃねえよ。";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "ああ、シャルル・ド・モール……お前も逮捕されて部下と一緒に牢に入るべきだが……銀行での一件は遺憾な誤解だったと判断された。";
				link.l1 = "この会話の始め方、気に入ったぜ、旦那。 "+GetFullName(NPChar)+"。すべて説明できる。";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "役人殿、あなたの牢にフォルケ・デルックという男がいると聞きました。彼の釈放のために私にできることはありますか？ ";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "役人殿、また来たぜ、囚人フォルケ・デルクの件だ。俺は彼の借金の権利を買い取った。 この男を俺の監督下に釈放してほしい。これが彼の借用証書だ、確認してくれ。";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "ごきげんよう、船長。何のご用でここへ？";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "ごきげんよう、副提督！どうなさいましたか？";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "閣下、総督閣下！ご命令はございますか？";
			}
			// <-- legendary edition
			link.l1 = "ああ、別に大したことじゃねえよ。ちょっと町を見て回ってただけで、たまたまここに来ただけさ。";
			link.l1.go = "exit";
			link.l2 = "ちょっと商売の話をしたかったんだ。";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "俺は牢屋の中に入りたいんだ。";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "おい、その囚人の名前は何の罪で捕まったのか教えてくれないか "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"何の罪で服役しているんだ？";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "哨戒船の元船長だと聞いた "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ここで拘留されています。彼と話してもよろしいですか？";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "I "+GetFullName(pchar)+"「総督の代理として、またその命令の下で行動して」 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"元船長と話す必要がある "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "これはあなたの娘さんのことだが…";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "お前に用があるんだ、役人。お前の任務に関わることだから、興味があるはずだぜ。";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "ある男について話がしたいんだ―― "+PChar.GenQuest.JusticeOnSale.SmugglerName+"。彼はあなたの捕虜ですよね、私の記憶が正しければ。";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "こんにちは、役人さん。私の知る限り、少し前に酔っ払った市民が通りで衛兵に喧嘩を仕掛けて拘束されたそうだ。"; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "士官殿、見張りと話をつけて、彼は主張を撤回した。これが彼からの証明書だ。"; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "はい？何か私に伝えたいことがあるのですか？";
			link.l1 = "最近、俺は通りで呼び止められているんだが "+pchar.GenQuest.Marginpassenger.Name+" 俺のために汚い仕事を手配してくれると申し出たんだ――つまり、「」という名の人物を捕まえて身代金を取るって話さ "+pchar.GenQuest.Marginpassenger.q1Name+"。それは "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "ふむ……それはとても興味深いな。どうぞ、続けてくれ！";
			link.l1 = "彼は自分が乗っていた船の名前を知っていた。 "+pchar.GenQuest.Marginpassenger.q1Name+" 航海を計画していたんだ。今は "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" 『』と呼ばれる"+pchar.GenQuest.Marginpassenger.ShipName+"「。それに、その船が出航する予定の時刻も教えてくれた。」";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "「それで、あいつは乗客を捕まえて身代金を要求しろと提案したのか？」";
			link.l1 = "その通りだ。身代金を受け取るために、俺は行くつもりだ "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+"、ある人物の名は "+pchar.GenQuest.Marginpassenger.q2Name+"。この情報には彼に金を払ったが、もちろん、その人物を誘拐するつもりはなかった。";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "それで俺に会いに来て、知らせてくれたってわけか？";
			link.l1 = "その通りです。あの悪党の行動は貴方の町の市民を脅かしていると私は確信しておりますので、 どうか適切な対策を講じていただきたいと願っております。";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "「私のところに来て正解だったな、」 "+GetAddress_Form(NPChar)+"「！この悪党め、」 "+pchar.GenQuest.Marginpassenger.Name+"、ずっと我々の監視下にあったのだ。俺が調査しよう。もしお前の言ったことがすべて確認できれば、 この野郎を半年間ぶち込んでやる。これで尊敬される市民に対してこんな企みをする気も失せるだろう！\nさて、正直さと善行への協力に感謝して、必ずやこの件を総督に報告しよう。当然ながら、それは総督の君への評価に――もちろん良い意味で――影響するだろう。協力ありがとう、船長！";
			link.l1 = "ふむ……どういたしまして、お手伝いできて光栄でした。さようなら！";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "聞く耳を持っているぜ。";
			link.l1 = "逃亡者を連れてきたぜ。";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "ああ、船長、本当にありがとうございます！彼女はどうですか？怪我はしていませんか？なぜ逃げたのです？なぜ？\n彼女には分からないのですか？花婿は裕福で重要な方なのですよ！若さというものは、無知で愚か……時には残酷です。覚えておいてください！";
			link.l1 = "まあ、あなたは彼女の父親で最終的な決定はあなたのものですが、結婚を急ぐ必要はないと思います…";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "何が分かるんだ？自分の子供はいるのか？いないのか？自分の子供ができたら、俺のところに来い、そしたら話をしよう。 \n彼女を家族のもとに連れ戻してくれた者には報酬を約束したんだ。";
			link.l1 = "ありがとう。あの女には気をつけたほうがいいぜ。俺の勘だが、あれで終わるような奴じゃねえからな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "俺は耳を傾けてるぜ、船長。";
			link.l1 = "あなたの守備隊の士官と海賊たちの間で行われている犯罪的な共謀についてお話ししたいのです（状況を説明する）。";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "ありがとうございます。"+GetSexPhrase("旦那","お嬢さん")+"！すぐにその悪党を逮捕するよう命令を出そう。\nしかし、あなたも出費があっただろうし、市の金庫は、あいにく空っぽでね……";
				link.l1 = "旦那！俺は金のためにやったんじゃねえ…";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "ありがとうございます。 "+GetSexPhrase("旦那","お嬢さん")+"！すぐにその悪党を逮捕するよう命令を出す。\n考えてみてくれ！我々はあいつの優秀な働きに対して個人用の武器を与えるところだったのだ。すべてが明らかになって、 本当に幸運だった。私は何も恥じることはない！";
				link.l1 = "「いつでも正義のために尽くすのは喜びだ。」";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("スター","「ss」")+"！あの士官とその手下どもが悪事を働いていると俺たちは前から疑ってたんだが、 あんたが証人もなしに奴らを始末したのは軽率だったと思うぜ。";
				link.l1 = "旦那！でも、自分を守らなきゃならなかったんだ…";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "船長、自分が何をしたかわかっているのか！？俺たちはこの罠を仕掛けるのに一ヶ月以上もかけてきたんだぞ！ それなのに、あんたの気まぐれで、俺たちの巡回隊と使者の会合を台無しにしやがって "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" それで今になってここへ来て自慢しに来たのか！？じゃあ、 この作戦にかかった全ての費用や経費をどう説明すればいいか、今度は俺に教えてくれるのか！？";
				link.l1 = "閣下！あなたはまったく要点を見ようとしていません…";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "この地図を見せてくれ……\n冗談じゃねえだろうな？こんなボロボロの羊皮紙が証拠だってのか？";
				link.l1 = "閣下！あなたは肝心な点をまるでご理解いただけていません……";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "これは全哨戒隊を壊滅させた理由としては斬新だな。まあ、ここに来てくれたおかげで、殺人犯を探す手間が省けたぜ。";
				link.l1 = "閣下！あなたはまったく要点を見ようとされませんね……";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "それでも、あなたの努力には報いるべきだと思います。さあ、この地図を受け取ってください。 これは最近絞首刑になった海賊の持ち物の中から見つかったものです。神のご加護があれば、 あなたが本当にその財宝を見つけられるかもしれませんが、私はあまり期待していません……";
			link.l1 = "ありがとうございます、とてもご親切ですね！";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "あなたの熱意は称賛に値します。どうぞ、この剣を報酬として受け取ってください――せめてものお礼です。それから、この地図もあなたに差し上げます。 諸島にはこういった偽物が山ほどあるでしょうからね。";
			link.l1 = "ありがとうございます、とてもご親切ですね！";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "そうかもしれねえ、そうかもしれねえ……まあ、この取引は神の正義と我らの主のお導きで決まったってことにしておこうぜ。";
			link.l1 = "ありがとうございます、とてもご親切ですね！";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "俺に説教なんかするんじゃねえ！俺にはお前がこの悪党どもと手を組んでるのが見え見えだぜ！\n衛兵ども、この“親切者”を捕まえろ！";
			link.l1 = "ありえねえ！";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "「それで、あいつに何の用だ？」";
			link.l1 = "私的な用件がいくつかあるんだ。";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "船長、私は「について尋ねる者は誰でも拘束し、邸宅へ送るように」という直接の命令を受けております "+pchar.GenQuest.CaptainComission.Name+"さらなる尋問のために。";
			link.l1 = "いい場所を構えてるじゃねえか！囚人の方から逮捕されに来るなんてな！";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "それでもなお、あなたに武器を差し出していただきたい！";
			link.l1 = "ふざけんな！力ずくで奪ってみろよ！";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "はい、もちろんです。この件については総督からあなたを支援するよう命じられています。今なら囚人に面会できます。";
			link.l1 = "「ありがとう…」";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "ええと、船長、俺にはこの囚人を釈放する権限がないんだ。総督に許可を求めてくれ。";
			link.l1 = "「役人殿、私は調査のために行動しています。囚人は当局に協力し、隠し場所を明かすことに同意しました。 時間が重要です――密輸業者どもが貴重な積荷を見つけてしまえば、それは民衆の手に渡らなくなります。」";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "殺すべきじゃなかったんだ、船長……まあ、俺には関係ないがな。だが、あんたの代わりに処刑しなきゃならん。\n衛兵！そいつを捕らえろ！";
            link.l2 = "俺に手を出すなんて、間違いだったな…";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "しかし、私が彼に護衛をつけることはできる。";
			link.l1 = "その必要はない――護衛は十分いるからな。それに、隠し場所が公になっては困る。";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "ふむ……まあいい。しかし、お前があいつの責任を命で取ることになるぜ。";
			link.l1 = "もちろんだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "今話せ、聞いているぞ。";
			link.l1 = "俺は船の書類を持っている。その持ち主が失くしたに違いねえし、あんたにとって興味があるかもしれねえと思ってな。";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "ふざけんな！俺の仕事の邪魔をするな！気になるなら港の役人のところへ行け！";
				link.l1 = "まあ、ありがとう、かな……";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "ああ、地元の持ち主だ。もしかすると賞品かもしれない "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" 警戒してくれたお礼にペソを十分な報酬として渡そう、船長。";
					link.l1 = "「そうでもないかもしれん。」";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "気前のいい申し出だな。書類はお前のものだ、さあ持っていけ！";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "おお、それは本当に面白いな！市の財務局が喜んで報酬を支払うだろう "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" 違法取引撲滅へのご協力へのペソです。";
						link.l1 = "「そうでもないかもしれん。」";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "気前のいい申し出だな。書類はお前のものだ、さあ持っていけ！";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "おお、主よ！あなたが私のもとに来てくださるとは、なんという幸運でしょう。 運の悪い同僚も喜んであなたに支払うことでしょう\n "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" この件を公にしないためのペソだ。";
						link.l1 = "「そうでもないかもしれない。」";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "太っ腹な申し出だな。書類はお前のものだ、さあ持っていけ！";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "ここは俺の街だ、船長。";
			link.l1 = "覚えておくぜ。";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "もちろん、すべて見ての通りだ――ここは何もかも完璧に整ってるぜ！";
				link.l1 = "よし、調べてみようか、中尉。";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "もちろんでございます、閣下。お通りください。";
				link.l1 = "ありがとうございます、士官殿。";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "さて、断る理由は見当たらないな――何しろ、あなたはその船の船長であり、仕えているのだから "+NationNameGenitive(sti(npchar.nation))+"。さあ、中へどうぞ。"; 
				link.l1 = "ありがとうございます、士官殿。";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("「でも、なぜそんなものが必要なんだ？信じてくれ、あそこには盗賊や山賊以外、何も面白いものなんてないぜ。」","その願いについてはすでに話し合っただろう。","またか？もう二回もその話をしたじゃねえか！","ふむ、またか……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("それでも、ぜひあなたのカスエマット見学に参加したいのです。とても興味があります！","ああ、その通りだ。だが、そのことについて話したかったんだ。","さて、三度目の正直かもな…","お前の捕虜たちが俺のもとから逃げ出さないことを願ってるぜ。",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "「まあ、断る理由はないな。」 "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - そして、牢獄を出るまでは、自由に廊下を歩いたり、囚人たちと会話したりしてもかまわない。";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "同意だ、ほら、これが約束の金貨だ！";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "それじゃ無理だ。廊下をただうろつくだけには重すぎるぜ。";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("いいや、これは規則で厳しく禁じられているんだ。\nなんだと？ここをサーカスか何かと勘違いしてるのか？消えろ、俺の仕事の邪魔をするな。","俺の牢屋を見知らぬ奴がうろつくのは許せねえ。頼むから、もう俺を邪魔しないでくれ！");
				link.l1 = "わかった、あんたの言う通りだな……";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "よし、今から探索を始めてもいいぞ……";
			link.l1 = "ありがとうございます、士官殿。";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "なるほど……その囚人を俺に引き渡せ、役人。こいつの運命は俺が決める。";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "なるほど……その囚人を俺に引き渡せ、役人。こいつの運命は俺が自分で決める。";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "なるほど……それで、買い戻しや保釈、あるいは他の方法で彼を解放する可能性はあるのか？";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "もちろん違うさ。あの絞首台送りの野郎はまっすぐ地獄行きだぜ。総督が特別に目を光らせてるからな！";
			link.l1 = "へぇ、そうか……";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "冗談か？あいつはとっくに絞首台行きだろう！もうすぐ縄と結婚するに違いねえ。もう忘れちまいな。";
			link.l1 = "了解だ。もう忘れちまったぜ……";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "そうは思わねえな。あいつはうちの町の連中にずいぶん迷惑をかけたんだ。だから、それを頼むんじゃねえぞ。";
			link.l1 = "ふむ、なるほど。";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "たぶん無理だな。あいつは泥棒だし、泥棒は牢屋に入ってなきゃならねえ。";
			link.l1 = "おお！よく言ったな、副官！";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "よくわからないな。奴が盗んだのはつまらない物だけだ。釈放するわけにはいかないが、 牢屋で腐らせておくのも確かに正しくないな。";
			link.l1 = "では、その者を俺に渡してくれ、中尉。保釈金は払うぜ――もちろん、妥当な額にな。";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "釈放するのか？まあ、ありそうだな。俺の考えじゃ、あんな小物の悪党をここに留めておく意味なんてねえよ。";
			link.l1 = "では、そいつを俺に引き渡してくれ、中尉。保釈金は払うぜ――もちろん、妥当な額にな。";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "ふむ……お前の言うことにも一理あるな。この浮浪者はここにいるべきじゃねえ――汚れと病気をばらまいてるだけだ……";
			link.l1 = "では、その者を俺に引き渡してくれ、中尉。保釈金は払うぞ――もちろん、妥当な額だがな。";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "よし、取引成立だ。 "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" きっちり払えば、今すぐそいつを連れて行っていいぜ。";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("素晴らしい！俺も賛成だぜ！","取引成立だな、役人！","素晴らしい。私はその拠出金を支払う準備ができている。");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "いや、それは高すぎるな。やめておくぜ。";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "よし、あいつの独房に行って、そのガキも連れていけ。";
			link.l1 = "ありがとう。";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "まあ、お前の選択だ。もう一度チャンスはやらねえぞ…";
			link.l1 = "必要ない。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "もちろんでございます、閣下。ご希望なら、この哀れな者をお引き取りください。ただし、 まだ犯罪者ですのでお気をつけくださいませ…";
			link.l1 = "それは素晴らしい。心配するな、中尉、俺は自分のやることが分かってる。";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "うーん……正直、どうしたものか……実のところ、囚人たちをただ解放するわけにはいかないんだ。しかし、君はまだ副提督だから、 この罪人を引き取る権利はあるはずだ。";
			link.l1 = "それは素晴らしい。心配するな、中尉、俺は自分のやることが分かってる。";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "総督閣下、閣下！どうぞお入りください、しかしご注意を。この犯罪者どもからは何が起きてもおかしくありません……";
				link.l1 = "心配するな、兵士よ、何かあれば俺が対処する。";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "ごきげんよう、副提督！私はここで勤務中です。許可なく誰も出入りしないよう見張っています。しかし、 あなたにはもちろん自由に通行する権利があります。";
				link.l1 = "それは素晴らしいな。";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("通ってよいぞ、看守が許可を出した。","牢番から命令を受けている。自由に通っていいぞ。");
				link.l1 = "「よろしい。」";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("看守長の特別な許可がなければ、これ以上先へは進めんぞ！","俺が答えるのは看守だけだ！あいつの許可なしで先に進もうとしたら、ただじゃ済まねえぞ！");
				link.l1 = RandPhraseSimple("なるほど","Alright")+"、兵士。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("俺は今、当番中だ。邪魔しないでくれ。","先へ進んでくれ、俺はお前と話しちゃいけないんだ。");
			link.l1 = "「よし、兵士。」";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("ほっほっ、いい時じゃねえか！","斬れ "+GetSexPhrase("相棒","娘")+"、切れ！！！","「ちくしょう！看守の死体を見るなんて、もう諦めてたぜ！」");
				link.l1 = RandPhraseSimple("へっ！","「アーッ！」");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("「待て、」 "+GetSexPhrase("相棒","娘")+"「くそっ、俺を放せ！」","「聞け、」 "+GetSexPhrase("相棒","娘")+"「どうか、牢の扉を開けてください。」");
					link.l1 = "「何のためだ？」";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("俺は強盗の罪を着せられてるが、俺は無実だ！","うぉお、きれいなツラしやがって……俺の牢屋でちょっと座っていくか！？ケッヘッヘッ……","俺は無実だ！");
				link.l1 = RandPhraseSimple("黙れ！","俺はお前なんかどうでもいいんだ……");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("「待て、」 "+GetSexPhrase("相棒","娘")+"、そんなに急いで行くなよ！","「急ぐな」 "+GetSexPhrase("相棒","娘")+"、話そう。");
					link.l1 = "「何のためだ？」";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "俺の話を聞けよ、相棒。俺が見た目悪いとか、そういうんじゃねえんだ。ただ、ここから抜け出したいだけなんだよ……";
			link.l1 = "「なんだって！？」";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "聞いただろう！俺を助けてくれよ、必ず恩は返すから…";
			link.l1 = "ほう、そりゃ面白いな。お前は何者だ、そして俺に何を差し出せるんだ？";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "私の名前は "+GetFullName(npchar)+"。俺はいくつかの物を安全な場所に隠してあるんだ。ここから出してくれたら、俺を連れて行ってくれ "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+"。そこだ、洞窟に俺の宝があるんだ。俺たちで持ち出して山分けしようぜ！";
			link.l1 = "「お前の隠し財産には何があるんだ？それに、どうやってお前が本当のことを言ってるって分かるんだ？」";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "俺は本当のことを誓って言ってるんだ！隠し場所についてだが――宝も金もあるんだ…";
			link.l1 = "いや、相棒。怪しい隠し財宝のために俺の命を張る気はねえ。悪いな……";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "さて、危険を冒す価値はあるかもしれねえ……こうしようぜ。俺が牢屋の見張りを片付けて、お前を俺の船まで連れていく。うまくいったら、 グロットに着くまでずっと俺のそばにいてほしいんだ\n  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+"……取引か？"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "よし、手伝ってみるぜ。牢屋の看守に話をしてみる。もしかしたら保釈できるかもしれねえ。";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "よし、信じてお前の牢を開けてやる。俺たちがあの洞窟に着くまで、ずっと俺のそばにいろよ。 "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+"……取引か？";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("くたばれ、この野郎！","くそっ、俺を盗みやがって、このクズめ……");
			link.l1 = RandPhraseSimple("あなたにも幸運を。さらば……","「月は犬の吠え声など気にしない……」");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "仕方ないな。俺に選ぶ余裕はないからな。";
			link.l1 = "よし。今からお前の錠を壊して外に出すぜ、それから一緒に進もう。準備はいいか？";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "「はい」 "+GetSexPhrase("相棒","娘")+"、準備できたぞ！";
			link.l1 = "じゃあ、始めようぜ！";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "いいだろう。俺に選り好みする余裕はないからな。";
			link.l1 = "よし。できるだけ早く俺について来い――まだ俺の船に行かねえといけねえんだ。ぐずぐずするなよ！";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "まあ、やってみてもいいぜ。うまく切り抜けられるといいな！でも時間を無駄にするなよ――二、三日もすれば俺はここを出るからな…";
			link.l1 = "ここで待っていろ、俺が全部手配する。";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "「さて、どうするんだ、」 "+GetSexPhrase("相棒","娘")+"?";
			link.l1 = "すべて手配済みだ、ここからお前を連れて行けるぜ。";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "じゃあ、ここから出よう！ああ主よ、なんて嬉しいんだ！";
			link.l1 = "まとめよう。俺が洞窟に着くまで、ずっと俺のそばにいてほしいんだ "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+"、一歩だけ後ろについてきてくれ。念のためにな。いいな？";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "もちろん、同意するぜ！ましてや、俺には選ぶ権利なんてねえからな。";
			link.l1 = "それなら、お前は自由だ。";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "「さて、どうする？」 "+GetSexPhrase("相棒","娘")+"?";
			link.l1 = "お前の釈放は手配できなかった。お前はこう告発されているんだ "+sTemp+"、そのため保釈はできません。";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "「でも俺は濡れ衣を着せられたんだ！ああ、悪魔め！これからどうすりゃいいんだ？ ここで生きたまま朽ち果てちまうのか！」";
			link.l1 = "悪いな、相棒。でも俺にできることは何もねえんだ。";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "残された手は一つだけだ――力ずくでお前を助け出すしかねえ。今すぐ錠を壊してお前を外に出す、そして俺たちは突破するぜ。覚悟はいいか？";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("呪われちまえ！","くそっ、俺を盗みやがって、このアマめ……");
			link.l1 = "あなたにも幸運を。さらば……";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "それで、何か良い知らせはあるか、 "+GetSexPhrase("相棒","娘")+"?";
			link.l1 = "お前の釈放の保釈金は高すぎる、そんな金は持ってねえ。もう助けるのはやめるしかない。";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "聞いてくれ、全部調べたが宝は見つからなかった。\nこんな結果になって残念だ。\n誰かが俺たちより先に掘り出したに違いねえ。";
					link.l1 = "「それはどういうことだ！？」";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "見つけたぞ！宝はまだ俺が置いた場所にある。";
					link.l1 = "素晴らしい。では、ここで別行動といこうか？";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "さて、これが俺の隠し財産だ。大した額じゃねえが、これが俺の全財産さ。約束通り、その半分はあんたのものだ。";
					link.l1 = "ああ、宝は確かに大したことねえな。\nまあ、何もないよりはマシだぜ。";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "船長、申し訳ないが……宝はないんだ。";
					link.l1 = "「なんだと！？俺を騙しやがったな、この野郎！あの島まで連れて行ってやったのに――なんのためだ？こんなこと、ただで済むと思うなよ！」";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "聞いてくれ、全部調べたが、宝は見つからなかったんだ。\nこんな結果になって残念だぜ。誰かが俺たちより先に掘り出したに違いねえ。";
                        link.l1 = "「それはどういうことだ！？」";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "くそっ……どうしてそんなことがあり得るんだ？そんなはずがねえ！";
                        link.l1 = "どうしたんだ、相棒？宝はどこだ？まさか、宝なんてねえって言うんじゃねえだろうな！";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "もちろん、約束通りだ。財宝の半分はお前のものだ。";
			link.l1 = "聖なる主よ、確かに貴重な品がたくさんあるな！";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "船長、他の品の中にあのインディアンの品もありますぜ。取り分とは別に、それも持っていっていいですよ。";
			link.l1 = "まあ、せめて解放のために何か価値のあるものはあるんだな！さっさと渡せ。";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "待ってくれ、船長、興奮しないで、説明させてくれ。俺もあんたと同じ水夫なんだ。間違って牢屋にぶち込まれたんだ、 誓って嘘じゃねえ。あんたが脱獄の唯一のチャンスだったから、宝のことは嘘をつくしかなかったんだ。\n宝なんてないが、そこに一つだけいい物を隠しておいた。それを持っていって、俺を静かに逃がしてくれ。もしかしたら、 いつか戦いの中で、それがあんたの命を救うかもしれねえ。";
			link.l1 = "まあ、どうせお前にはあまり期待してなかったぜ。\nありがたいことに、俺は根に持つタチじゃねえからな。";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "いやぁぁぁ！！！ここにはない！くそったれな紙切れめ……船長、俺は絶対ここで見つかると思ってたんだ！だが、どうやら俺の勘違いだったらしい！ あの紙切れに書いてあったこと、どうにもはっきりしなかったんだよ……";
			link.l1 = "まあまあ……お前さん、本当にやばい状況だぜ。だが、それでも説明を聞かせてもらおうか。";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "俺は地図の切れ端を持ってたんだ。本物の地図だったんだぜ、誓ってもいい！でも、 どの島が描かれてるのか見分けるのはすごく難しかった……ここだと思ってたんだ……でも、見ての通り、俺の勘違いだったな。";
			link.l1 = "何の紙切れだ？今すぐ俺によこせ！";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "もちろん、持っていけ。船長、俺を放してくれ…頼むよ？本当にあそこに宝があると信じてたんだ。もしかしたら、 あんたが場所を突き止めて自分のものにできるかもしれない。頼む、お願いだ。";
			link.l1 = "なるほど……確かに、その切れ端だけじゃ何も分からねえな。地図の後半が必要だ。よし、もう行け。 今ならお前のせいじゃなかったって分かるぜ。";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "「とても簡単だ」 "+GetSexPhrase("相棒","娘")+"。人生には何でも起こるものさ。\nまあ、お前はここにいる――好きにしろよ。残ってもいいし、他を探してもいい。さて、俺は行かなくちゃな！\nじゃあな、 "+GetSexPhrase("友よ","娘")+"、命を救ってくれてありがとう。あなたのことは一生忘れない！";
			link.l1 = "この野郎！俺がそんなことを見逃すと思ってんのか！？おい！待て、腰抜け！";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "はい、どうぞ。ありがとうございます！";
			link.l1 = "さらば……";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "ありがとうございます、船長！残りの人生ずっとあなたのために祈ります！";
			link.l1 = "ああ、うるせえ！さっさと行けよ……";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "私は呼ばれている "+GetFullName(npchar)+"……君に頼みがあるんだ、へへ……";
			link.l1 = "どうした？";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "牢屋から手紙を出したいんだ。お前、やってくれるか？";
			link.l1 = "「で、俺にはどんな得があるんだ？」";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "奴らは絶対にあんたを裏切らねえ、俺が保証するぜ……どうだ？乗るのか？";
			link.l1 = "いや、興味はねえ。";
			link.l1.go = "Prisoner_5";
			link.l2 = "まあ、俺にあまり手間がかからないなら、やってやってもいいぜ。";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "よし。じゃあ、よく聞け。仲間が二人、家の中で俺の伝言を待ってるんだが、襲撃の時に捕まらないようにしてるんだ。 ただ、どの家かは俺にも分からねえ。お前が探すしかねえぞ。";
			link.l1 = "「捜索ってどういう意味だ？」";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "探すっていうのは、まさに探すってことだ。町中を走り回って、家々を覗き込むんだ。正しい場所にたどり着いたら、 話をするまで帰してもらえねえだろう。だがな、俺ならせいぜいあと二日しかそこにいねえ。だから、ぐずぐずするなよ。 ";
			link.l1 = "なるほど。では、その書状を渡してくれ。";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "ふん、あんたのことが気に入らねえな。気が変わった。さあ、ついて来い、突っ立ってないで！";
				link.l1 = "見てみろよ！まあ、お前の好きにしな。";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "「どうぞ。ありがとうございます。」 "+GetSexPhrase("相棒","娘")+"!";
				link.l1 = "全然違う。";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "「ああ、奴は密輸の容疑で逮捕されたよ。しかし、なんであんな絞首台送りの野郎のことを気にするんだ？」 "+GetAddress_Form(NPChar)+"?";
			link.l1 = "奴の一味は、奴を逃がして悪事を続けるつもりだ。";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "彼は無実だったと聞いた。";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "「総督に知らせなければならない」 "+GetAddress_Form(NPChar)+"、こいつら悪党どもは全員捕まえなきゃならねえ！";
			link.l1 = "その通りにするぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "「聞け、」 "+GetFullName(PChar)+"「その男は禁制品を町の中で売ろうとして捕まったんだぞ！どうして無実だなんて言えるんだ？」";
			link.l1 = "その告発には根拠がなく、証拠もないと聞いたが、そうなんだろう？冤罪の男をただ拘束するわけにはいかないぞ。";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "証人も品物もないが、それでも何も変わらねえぜ、船長 "+GetFullName(PChar)+"！あの人物は間違いなく有罪だ――しかも違法取引だけじゃないかもしれない。どちらにせよ、なぜお前はその囚人にこだわるんだ？";
			link.l1 = "「もしかして、あの哀れな囚人の保釈金代わりに俺の言葉が役に立つか？」";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "もしかすると、この5000ペソがあの哀れな囚人の保釈金になるかもしれませんね？";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "「よし、」 "+GetAddress_Form(NPChar)+"、そいつを連れてさっさと出ていけ、気が変わらないうちにな。";
				link.l1 = "正義が勝つのを見るのは素晴らしいことだと思わないか？";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "「いや、」 "+GetAddress_Form(NPChar)+"、それじゃ困る。";
				link.l1 = "それなら、この五千ペソがもっと説得力のある理由になるんじゃねえか？";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "「よし、」 "+GetAddress_Form(NPChar)+"「その悪党を連れてさっさと行け、俺の気が変わらないうちにな。」";
			link.l1 = "正義が勝つのを見るのは気持ちいいだろう、そう思わねえか？";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "ああ、そんな乱暴者がいたよ。見張りに無礼を働いて、その後喧嘩になったんだ。それだけさ。 数日間牢に入れて頭を冷やさせるだけだ。\nなぜあいつのことを気にするんだ？あんたは船長のようだが、あの酔っ払いは水夫には見えないぜ。";
			link.l1 = "ああ、そうだ、俺は船長だ。実はな、この酔っ払いは俺の古い知り合いなんだ。だから、 このことは誰にも言わないでくれよ。俺の理解が正しければ、あいつは武器すら抜いていないはずだ。 今回は俺の顔を立てて、あいつを見逃してくれないか？";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "ああ、俺の親友さ。心配すんな、誰にも言わねえよ。実際、あいつはまともに一発も入れられなかった。 ただの未遂だったから牢に入れられたんだ。あんたが頼むなら、あんたへの敬意を込めて釈放してやるよ。ただし、 次は自制するようにしっかり言い聞かせてくれ。いや、むしろ酒を控えさせたほうがいいぜ。";
				link.l1 = "ありがとうございます、士官殿。";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "ああ、いい友達だな。心配するな、誰にも言わねえよ。ただな、あいつは縛られる前に見張りの顔を殴っちまったんだ。 だから、俺はあいつを出してやれねえ。もちろん、見張りが訴えを取り下げるって言うなら別だがな。 自分で話してみろよ、今日は町の周りを巡回してるぜ。";
				link.l1 = "いいえ、もし彼が衛兵を殴ったのなら、私にはどうにもできません。彼には数日間ここにいてもらうしかありません。 ご迷惑をおかけして申し訳ありません、役人殿。";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "よし、俺が行って見張りと交渉してみるぜ。";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "ああ、いい友だちだな。心配するな、誰にも言わねえよ。ただな、勤務中の軍人を襲うのは犯罪だぜ。まあ、 間を取って釈放してやることはできるが、保釈金が必要だ。";
				link.l1 = "「それにはいくら払えばいいんだ？」";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "＊読む＊　そうか……そうか……まあ、見張り番が文句を言ってないなら、俺も文句はねえ。友達を連れてっていいぜ。ただし、 次はもう少し自制するように言っとけ。できれば、酒も控えさせろよ。";
			link.l1 = "ありがとうございます、士官殿。";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "まあ、武器を取らなかったから、たったの1,500ペソだな。";
			link.l1 = "そんな大金はまだ出せそうにないな。まあ、彼はここに数日しかいないんだし、害はないだろう。\nもしかしたら酒も控えるかもしれないな。";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "よし、保釈金を払う準備はできてるぜ。";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "友達を迎えに来てもいいぜ。ただし、次は自制するように言っとけ。いや、むしろ酒を控えさせたほうがいいな。";
			link.l1 = "ありがとうございます、士官殿。";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "虐殺を始める代わりに来てくれてありがとう。最近は少なくとも誰かが分別を持ってくれているな。";
				link.l1 = "それで、何のご用件でございますか、旦那士官？私が中国人を探していることと関係があるのですか？";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "自分から来てくれて助かったぜ。最近は厄介者にはもううんざりなんだ。";
				link.l1 = "ご覧の通り、俺は乱暴者じゃねえよ。だがな……なぜ俺がここにいるんだ、役人さん？お前の部下たちにも聞いたが、まだ答えをもらってねえ――もしかして、町である中国人を探してるからか？";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "もちろんそんなことありません！どうぞ、お入りください。うちの牢獄はいつでも歓迎ですよ。あ、いや、 いい意味で言ってますからね。で、今日はどういったご用件でしょうか？";
			link.l1 = "ああ、別に特別なことはないさ、ちょっと街を見て回ってただけで、たまたまここに来ただけだよ。";
			link.l1.go = "exit";
			link.l2 = "ちょっと商売の話をしたかったんだ。";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "俺は牢屋の中に入りたいんだ。";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}

// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("First Shipyard Visit " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴っていて、みんながお前を探している。俺だったら、ここにはいないぜ。","街の衛兵どもがみんなお前を探して町中を捜索しているんだ。俺は馬鹿じゃねえ、話なんかしねえぞ！","走れ "+GetSexPhrase("相棒","娘")+"……兵士たちに蜂の巣にされる前にな……"),LinkRandPhrase("何の用だ、 "+GetSexPhrase("ろくでなし","くせえ野郎")+"？！街の衛兵どもはもうお前の匂いを嗅ぎつけてるぜ、汚ねえ海賊野郎、逃げ切れると思うなよ！","殺人者め、今すぐ俺の家から出て行け！衛兵！","「俺はお前なんか怖くねえ」 "+GetSexPhrase("ろくでなし","ネズミ")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には問題ねえさ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("「黙れ、」 "+GetWorkTypeOfMan(npchar,"")+"、さもないと舌を引き抜いてやるぞ！","へっ、 "+GetWorkTypeOfMan(npchar,"")+"、そしてあそこでも――海賊退治だ！だから言うんだ、相棒、黙ってりゃ死なずに済むぜ！"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "何かご用ですか、旦那？";
					Link.l1 = "お前の船を見に来たんだが……今はちょっと忙しいんだ。まだ片付いてない用事があるんでな。\nそれが済んだらまた来るぜ。";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "何かご用ですか、旦那？";
					Link.l1 = "聞いてくれ、あんたから船を買いたいんだ。";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "他にご用はございますか、旦那？";
				Link.l1 = "いや、そうじゃないと思う。";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "これで終わりだぜ、船長。仕事は片付いた。さて、楽しみな時間だ――コインの音を聞かせてくれ。ちょっと待ってな……";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "役人、待ってくれ！頼む！これは何かの間違いだ。旦那、船長はこれに全く関係ないんだ、 ただ船を修理するためにここに寄港しただけだよ。ちょうど出航するところだったんだ。それに樽って？ 何の話をしているんだ？";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "「役人さん、もう一度言うが、船長は船の修理代を払いにここへ来たんだ。この樽は俺の所有物で、 製造のためだけに使うものだ。俺は熟練の造船職人で、この樹脂は俺が造る船のためのものだ。」";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "ああ、船長旦那！俺がどれほどひどい目に遭ったか、想像もつかねえだろう。二日間も地下牢にぶち込まれて、 ネズミやら鼠やら、ろくでもねえ連中に囲まれてよ！持ってるツテを総動員して、やっと抜け出せたんだ。ああ、 この新鮮な空気よ！";
					link.l1 = "お気の毒に思いますよ、旦那。\nで、俺たちの樹脂はどうなります？それと、俺の金貨は？";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "おお、またお前か！見覚えがあるぞ、若いの！最近、 絹の帆布で船の速度を上げる方法について聞いてきたのはお前だったな？";
				link.l1 = "「記憶力が素晴らしいですね、旦那。」"; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("ははっ！本物の古強者が俺の小さな工房に来てくれたとはな！この海域は初めてかい、船長？","いらっしゃい、旦那！海に馴染みがあって船をお持ちなら、まさにここがうってつけの場所ですよ！","こんにちは、旦那！運がいいですね――ここは英国領新世界で一番の船工房ですよ。"),LinkRandPhrase("旦那、あんたはきっと腕利きの船長だろう？そうなら、俺のささやかな造船所に来て正解だぜ！","ここは初めてかい、船長旦那？中へどうぞ、この老いぼれ船大工に会ってくれ。","お近づきになれて光栄です、旦那！船は女と同じで、優しく扱わなきゃならん――フランス男はその道の達人だぜ！俺を信じな、ここに来て後悔はさせねえよ！"),LinkRandPhrase("ここでお前を見たことはねえな、旦那。会えて嬉しいぜ！","海の勇敢な征服者に挨拶するぜ！あんたは船乗りだろ？俺はここの船大工だ。お互い知り合っておくべきだな。","やあ、旦那！俺の工房へようこそだぜ！"),LinkRandPhrase("ごきげんよう、旦那。お会いするのは初めてですね？何かご用でしょうか？","やあ、船長旦那。驚かないでくれ、俺は今までに何人もの船長を見てきたから、あんたも一目で船長だと分かったのさ。","どうぞお入りください、旦那。私はこの地の船大工です。お会いできて光栄です。"));
				Link.l1 = LinkRandPhrase("俺も会えて嬉しいぜ。俺の名前は "+GetFullName(pchar)+"、それに俺はこの辺りは初めてなんだ。だから、ちょっと立ち寄ってみたのさ。","通り過ぎるわけにはいかなかったんだ――わかるだろ、削りたての板の香り……俺は "+GetFullName(pchar)+"、「『」の船長"+pchar.ship.name+"「。」","自己紹介させていただきますが― "+GetFullName(pchar)+"、「『」の船長"+pchar.ship.name+"、はじめまして。ここで船の建造や修理をしているんだな？");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "ごきげんよう、MacArthur船長。";
					link.l1 = "ヘレンと呼んでくれればいいよ、旦那 "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("おお！この辺りの水域の恐怖だな、船長 "+GetFullName(pchar)+"！何かご用ですか？","「さっそく本題に入ろうぜ」 "+GetAddress_Form(NPChar)+"、世間話してる暇はねえんだ。修理が必要なのか、それとも船を丸ごと替えたいのか？","「ああ、それじゃねえか」 "+GetFullName(pchar)+"「！どうした、」 "+GetAddress_Form(NPChar)+"どうした？お前の船に何か悪いことでも起きたのか？"),LinkRandPhrase("今度は何の用だ、船長？全く休む暇もねえな――いつもこの悪党どもばかり、なんて呪われた日だ……","「やあ、」 "+GetAddress_Form(NPChar)+"。正直に言うと、あんたの来店で客がみんな逃げちまったぜ。注文でその損失を埋めてくれるんだろうな？","「俺に用か」 "+GetAddress_Form(NPChar)+"？さっさとやれ、急げよ。"),LinkRandPhrase("何の用で俺のところに来たんだ、旦那 "+GetFullName(pchar)+"……？あんたの暮らしぶりを考えりゃ、船が苦労してるのも無理はねえな……","高貴なお方をお迎えできて嬉しい……あっ、失礼しました、 "+GetAddress_Form(NPChar)+"、人違いだったな。何の用だ？","あんたみたいな奴は好きじゃねえが、追い返す気もねえ。何の用だ、船長？")),LinkRandPhrase(LinkRandPhrase("お会いできて本当に嬉しいですよ、旦那 "+GetFullName(pchar)+"！それで、調子はどうだ？修理か艤装の手入れが必要か？","「いらっしゃいませ」 "+GetAddress_Form(NPChar)+"「おい！船長」 "+GetFullName(pchar)+" いつでも俺の工房の歓迎すべき客だぜ！","「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！また俺に会いに来たのか！お前の美しい船は元気かい、どうだ？"),LinkRandPhrase(""+GetAddress_Form(NPChar)+"、また会えて本当に嬉しいよ！君の美しい船はどうだい？何か手伝えることはあるかい？","「ああ、」 "+GetAddress_Form(NPChar)+"「やあ、船長！調子はどうだ？マストがきしんでるのか、それともビルジの掃除が必要か？ 俺の連中が全力でやらせてもらうぜ！」","「こんにちは、船長」 "+GetFullName(pchar)+"。 また立ち寄ってくれて嬉しいよ、いつでも力になるぜ。"),LinkRandPhrase("お越しいただき嬉しいです、船長！あなたは大歓迎のお客様ですよ。 "+GetAddress_Form(NPChar)+"、そして、そのままでいてほしい。","「ああ、」 "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"！本当にあなたが来てくれて嬉しいよ！何かご用かい？","船長、またお越しになりましたね "+XI_ConvertString("Colony"+npchar.City+"Acc")+"！信じてくれ、俺たちも本当は力になりたいんだ。")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("道具を持ってこい、旦那。静かにしてくれ、いいな？今はそんな気分じゃねえんだ。","くだらねえ話はやめろ、相棒！俺が欲しいのはお前の助けであって、無駄口じゃねえんだ。"),RandPhraseSimple("俺が金を払う――お前は黙って働け。わかったか？","おい、相棒、みんな追い払ってくれよ――俺だぜ、お前の一番のお得意様が来たんだ！")),RandPhraseSimple(RandPhraseSimple("俺も会えて嬉しいぜ、旦那。だが、あいにく時間がねえんだ。さっさと本題に入ろうじゃねえか。","俺も会えて嬉しいぜ、相棒。お気に入りの客を手伝ってくれるか？"),RandPhraseSimple("こんにちは、相棒。さっそく本題に入ろうぜ。次は必ず一緒に酒でも飲もうや。","お会いできて嬉しいです、旦那。\nいつお越しいただいても嬉しいですが、今はあなたの助けが必要です。")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "俺の船に大砲が必要だ。";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "他のどの造船所にもない特別なものを用意できるか？";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "「よそ者の助けが必要な仕事はないのか？」";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "高品質なヨーロッパ製の建築用、鍛冶用、測定用の道具一式を買いたいんだ。手伝ってくれるか？";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "建築用具一式のためにドゥブロン金貨を持ってきたぜ。";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "俺がお前に届けた "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+"、ご要望通りです。";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "盗賊を突き止めて取り戻した "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "俺の帆の見た目を変えたいんだ。";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "ちょっと話がしたかっただけだ。";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "金銭の件についてお話ししたいのですが。";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("俺はある男の依頼でここに来た。その名は総督だ。 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 俺をあんたのところに寄越したんだ。何か受け取ることになっててな……");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "俺はその船の設計図を持ってきたんだ "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "こんにちは、あなたの息子さんの招きで来ました。"; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "これはあなたの娘さんのことだが……";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "俺は行かなくちゃならねえ。";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "新しいお客さんにお会いできてとても嬉しいです。\n私の造船所はあなたのためにございます。";
				Link.l1 = "「素晴らしい」 "+GetFullName(NPChar)+"。さて、どんな品を見せてくれるんだ？";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "俺の船に大砲が必要だ。";
					link.l13.go = "Cannons";
				}									
				link.l15 = "よそ者の手助けが必要な仕事はないのか？";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "俺の帆の見た目を変えたいんだ。";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "ちょっと話がしたかっただけだ。";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "金銭の件についてお話ししたいのですが。";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("俺はある男の依頼でここに来た。その名は総督だ。 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 俺をあんたのところに寄越したんだ。何かを受け取ることになっててな……");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "俺はその町から船の設計図を届けた "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "こんにちは、あなたの息子さんの招きで来ました。"; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "これはあなたの娘さんのことだが……";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "この書類の持ち主について何か知っているか？";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "俺は行かなくちゃならねえ。ありがとう。";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "もちろん、MacArthur船長、ご要望通りに。今日は何をご用件ですか？";
				Link.l1 = "「素晴らしい」 "+GetFullName(NPChar)+"。さて、どんな品があるか見せてもらおうか。";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "俺の船に大砲が必要だ。";
					link.l13.go = "Cannons";
				}									
				link.l15 = "よそ者の手を借りたい仕事はないのか？";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "俺の帆の見た目を変えたいんだ。";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "ちょっと話がしたかっただけだ。";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "金銭の件についてお話ししたいのですが。";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("俺はある男の依頼でここに来た。その名は総督だ。 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 俺をあんたのところに寄越したんだ。何か受け取ることになっててな……");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "俺はその町から船の設計図を届けた "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "こんにちは、あなたの息子さんの招待で来ました。"; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "これはあなたの娘さんのことだが……";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "この書類の持ち主について何か知っていることはあるか？";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "俺は行かなくちゃ、ありがとう。";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "うちの造船所は船の改造で有名だぜ。興味あるか、船長？";
			Link.l1 = LinkRandPhrase("素晴らしい！俺の船を見て、どうすればもっと良くなるか教えてくれないか？","それはとても興味深いですね、旦那！それで、俺の船には何をしてくれるんだ？","ふむ……俺は自分の船に愛着があるが、もし本当に面白い提案があるなら、考えてやってもいいぜ。どうだ？");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "うーん……俺は小舟なんか扱わねえよ。どれだけ手をかけても、ボロ船は所詮ボロ船だぜ。";
					Link.l1 = "なるほど……";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "まあまあ…さて、ここに何があるか見てみよう…よし― "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+"。あなたの船はすでに改良された特性の最大数に達しています。これ以上手を加えても意味がなく、 かえって害になる恐れがあります。";
					Link.l1 = "なるほど……";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "船を改造する前に、まず完全に修理しなければならん。それもまた、ここ俺の造船所でできるぜ。";
					Link.l1 = "承知した……";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "速度を上げろ。";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "風に対して角度を上げろ。";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "待てよ！やっぱり気が変わった。";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "速度を上げろ。";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "待て！やっぱり気が変わった。";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "風に対して角度を広げろ。";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "待て！やっぱり気が変わった。";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("おお！俺の船はもうこの方法で改良済みだぜ。まあ、時間を取らせて悪かったな！","ありがとうございます、旦那。でも俺はすでにアップグレードを持っていて、それはまさにあんたが言ってたやつなんだ。 他の船や船長たちにも幸運を祈るぜ！","へっ！俺の船は前の持ち主がすでに改装してたってことか――きっとこの造船所でやったんだろうな。まあ、その先見の明に感謝しないとな。そして、 あんたと職人たちの見事な仕事にも礼を言うぜ！");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "最大搭載砲数を増やす。";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "載貨重量を増やせ。";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "待て！やっぱり気が変わった。";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "最大搭載砲数を増やす。";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "待て！やっぱり気が変わった。";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "載貨重量を増やせ。";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "待て！やっぱり気が変わった。";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("おお！俺の船はもうこの方法で改良済みだぜ。まあ、時間を取ってくれてありがとな！","ありがとうございます、旦那。でも俺はもうアップグレードを持っていて、 それはまさにあんたが言ってた通りのものなんだ。他の船や船長たちにも幸運を祈るぜ！","へっ！俺の船は前の持ち主がすでに改装してたってことか――きっとこの造船所でやったんだろうな。まあ、その先見の明に感謝しないとな。それから、 お前さんと職人たちの見事な仕事にも礼を言うぜ！");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "船体の耐久性を上げてくれ。";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "乗組員収容スペースを増やす。";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "待て！やっぱり気が変わった。";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "船体の耐久性を強化してくれ。";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "待て！やっぱり気が変わった。";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "乗組員収容スペースを増やす。";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "待て！やっぱり気が変わった。";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("おお！俺の船はもうこの方法で改良済みだぜ。まあ、時間を割いてくれてありがとうな！","ありがとうございます、旦那。でも俺はすでにアップグレードを持っていて、 それはまさにあんたが言ってた通りのものだ。\n他の船や船長たちにも幸運を祈るぜ！","へっ！俺の船は前の持ち主がすでに改装してたってことか――きっとこの造船所でやったんだろうな。まあ、その先見の明に感謝しねえとな。それと、 お前さんと職人たちの見事な仕事にも礼を言うぜ！");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "操縦性を上げてくれ。";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "最小乗組員数を減らせ。";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "待て！やっぱり考え直した。";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "操縦性を上げてくれ。";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "待て！やっぱり考え直した。";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "最小乗組員数を減らせ。";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "待て！やっぱり気が変わった。";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("おお！俺の船はもうこの方法で改良済みだぜ。まあ、時間を取ってくれてありがとうな！","ありがとうございます、旦那。でも俺はすでにアップグレードを持っていて、 それはまさにあんたが言ってた通りのものだ。\n他の船や船長たちにも幸運を祈るぜ！","へっ！俺の船は前の持ち主がすでに改装してたってことか――きっとこの造船所でやったんだろうな。まあ、その先見の明に感謝しなきゃいけねえし、 あんたと職人たちの見事な仕事にも礼を言うぜ！");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "船はどこだ？俺をからかってるのか、それとも何か企んでるのか？";
			    Link.l1 = "ああ、俺の勘違いだった……すまねえ。";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
			    link.l1 = LinkRandPhrase("お待たせすることはありませんよ。こういう問題は私がすぐに解決できますから、安心してくださいね？","もう持っていると思ってくれ、そして俺のためにドックを押さえておいてくれ。俺は風のように素早く戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねるだけさ、ははっ！");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預け金が見当たらねえな……";
				link.l1 = "後で寄るぜ。";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "時が過ぎて、船は待っている。俺が頼んだものは全部持ってきたか？";
			    Link.l1 = "ああ、何か見つけることができたぜ。";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "いや、まだ作業中だ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをしたあとで船を変えたのか？そんなことしちゃいけねえよ。";
			    Link.l1 = "ああ、すべては状況のせいだ！預け金が失われたのは残念だな…";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものは全部そろった。じゃあ、作業に取りかかるとするか。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "俺にはまだ必要なものがある：アイアンウッド－ "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "いいだろう。";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.35);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "……どうやらこれで全部だ……今なら船倉を満載できるぜ、俺の仕事の質は保証する。";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありません、安心してください。こういった問題なら、俺がすぐに解決できるからな、いいか？","もう持っていると思ってくれ、俺のためにドックを押さえておいてくれ。風のようにすぐ戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねてくるだけさ、ははっ！");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預け金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "時が過ぎ、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "ああ、何か見つけることができたぜ。";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "いや、まだ取りかかってる最中だ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("テール","ｓ")+"、取り決めをしたときから船を変えたのか？それはしない方がよかったんだが。";
			    Link.l1 = "ああ、すべては状況次第だ！預け金がなくなったのは残念だな…";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものはすべて揃った。じゃあ、作業に取りかかるとするか。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "俺にはまだ必要なものがある：船用シルク－ "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "いいだろう。";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.35);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.3 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "…すべて準備できてますぜ、船長。帆をいっぱいに張って風をつかんでください。気になるなら、 ご自身で確かめてみてください！";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "いや、そりゃ俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("ご安心ください、長くお待たせすることはありません。こういう問題なら、俺に任せてくれ、いいな？","もう持っているものと思って、俺のためにドックを確保しておいてくれ。俺は風のように素早く戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねるだけさ、ははっ！");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預け金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "時は流れ、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "ああ、何かを届けることができたぜ。";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "いや、まだ取りかかっているところだ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをした後で船を変えたのか？そんなことしちゃいけねえぞ。";
			    Link.l1 = "ああ、すべては状況のせいだ！預け金が失われたのは残念だな…";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものは全て揃った。では作業に取りかかるとしよう。";
			    link.l1 = "待ってるぞ。";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "俺にはまだ必要なものがある：ロープ― "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "「いいだろう。」";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "…すべて準備が整ったはずだ…今すぐ舵を確認してくれ、船長！";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要な物は何でも持ってくる。";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありませんよ。こういう問題なら、俺がすぐに片付けてやるからな、いいか？","もう持っているものと思って、俺のためにドックを押さえておいてくれ。俺は風のように素早く戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねてくるだけさ、ははっ！");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預かり金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "時は過ぎ、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "「ああ、何か見つけることができたぜ。」";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "いいや、まだ作業中だ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをした後で船を変えたのか？そんなことしちゃいけねえぞ。";
			    Link.l1 = "ああ、すべては状況のせいだ！預け金が失われたのは残念だな……";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものはすべて揃った。では作業に取りかかるとしよう。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "俺がまだ必要なのは：鉄木だ－ "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "いいだろう。";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.35);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "…終わりました、船長。これでさらに水夫を雇えます、全員分のスペースは十分にあります。";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありませんよ。こういう問題なら、俺に任せてくれ、いいな？","もう持っていると思ってくれ、そして俺のためにドックを押さえておいてくれ。俺は風のように素早く戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねるだけさ、ははっ！");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預かり金が見当たらねえな……";
				link.l1 = "後で寄らせてもらうぜ。";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "時が過ぎて、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "ああ、何とか見つけたぜ。";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "いや、まだ取り掛かっているところだ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをした後で船を変えたのか？そんなことしちゃいけねえよ。";
			    Link.l1 = "ああ、すべては状況のせいだ！預け金が失われたのは残念だな……";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものはすべて揃った。では作業に取りかかるとしよう。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "まだ必要なのは……ロープだ―― "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "いいだろう。";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.35);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "…準備完了だ、船長！これで同じ成果を出すのに、より少ない船員で船を操れるぜ。";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありませんよ。こういう問題なら、俺がすぐに解決できるからな、いいな？","もう手配してくれているものと思って、俺のためにドックを確保しておいてくれ。俺は風のように素早く戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねるだけさ、ははっ！");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預かり金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "時が過ぎて、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "ああ、何か見つけることができたぜ。";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "いいや、まだ作業中だ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをした後で船を変えたのか？そうするべきじゃなかったぜ。";
			    Link.l1 = "ああ、すべては状況のせいだ！預け金が失われたのは残念だな……";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものは全部そろった。じゃあ、作業に取りかかるとするか。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "俺にはまだ必要なものがある：樹脂－ "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "いいだろう。";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.35);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
					}
				}
				else
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
					}
				}
			}
	        shTo.Tuning.HP = true;
			ProcessHullRepair(pchar, 100.0); // у нпс при апгрейде есть, здесь тоже должно быть

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "…これでよし…これからはお前さんの船の船体をぶっ壊すのは、敵にとっちゃずっと難しくなるぜ！";
			Link.l1 = "へへっ、あんたの言葉を信じるぜ！ありがとう、旦那。";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありません、必ずすぐに対応します。こういう問題は俺に任せてくれ、いいな？","もう手に入れたものと思って、俺のためにドックを押さえておいてくれ。風のようにすぐ戻るぜ。","もちろんだ。頼まれた品を持ってる連中を何人か訪ねるだけさ、ははっ！");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "預かり金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "時は流れ、船は待っている。俺が頼んだ物は全部持ってきたか？";
			    Link.l1 = "ああ、なんとか品物を届けることができたぜ。";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "いいや、まだ作業中だ。";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをした後で船を変えたのか？そんなことしちゃいけねえよ。";
			    Link.l1 = "ああ、すべては状況次第だな！預け金が失われたのは残念だ……";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "素晴らしい、これで必要なものはすべて揃った。では作業に取りかかるぞ。";
			    link.l1 = "待っている。";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "俺はまだ必要なんだ：船用の絹－ "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "「いいだろう。」";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "…準備完了だ、船長！…これであんたの船は向かい風でもずっと速く進めるぜ。";
			Link.l1 = "ありがとう！試してみるぜ。";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "承知した。条件を受け入れる。必要なものは何でも持ってくる。";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "いや、それは俺には合わねえな。";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "素晴らしい。材料を待っているぞ。";
				link.l1 = LinkRandPhrase("お待たせすることはありませんよ。こういう問題なら、俺がすぐに片付けてやるからな、いいな？","もう持っていると思って、俺のためにドックを押さえておいてくれ。風のようにすぐ戻るぜ。","もちろんだ。あんたが頼んだ品を持ってる連中を何人か訪ねるだけさ、ははっ！");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "預かり金が見当たらねえな……";
				link.l1 = "後でまた寄るぜ。";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "時が過ぎて、船は待っている。俺が頼んだものは全部持ってきたか？";
				Link.l1 = "「ああ、何か見つけることができたぜ。」";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "いいや、まだ作業中だ。";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ター","ｓ")+"、俺たちが取り決めをしてから船を変えたのか？そんなことしちゃいけねえよ。";
			    Link.l1 = "ああ、すべては状況次第だな！預け金が失われたのは残念だ…";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "素晴らしい、これで必要なものはすべて揃った。では作業に取りかかるとしよう。";
				link.l1 = "待っている。";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "俺にはまだ必要なものがある：樹脂― "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "「いいだろう。」";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "…以上だ、船長。追加の大砲を使えるぜ――もし持ってりゃな、へへ。";
			Link.l1 = "ありがとう！";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "解決しなければならない用件があるんだ。船の注文が入っていてな― "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+"。しかし、今うちの造船所にはそのような船はなく、今後二ヶ月以内にも手に入れる手段はありません。\nもしその船を用意してくれるなら、心から感謝しますし、販売価格の一・五倍で買い取ります。";
					link.l1 = "面白い提案だな。乗ったぜ！";
					link.l1.go = "Findship";
					link.l2 = "俺には興味ねえな。";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "ちょうどいいところに来てくれた。もしかしたら手を貸してくれるかもしれない。昨日、 誰かにとても貴重な道具を盗まれてしまったんだ―― "+pchar.GenQuest.Device.Shipyarder.Type+"……もう一つ作る手立てもないし、ヨーロッパから取り寄せる時間も費用もないんだ。それがなければ、 まともに船を造ることもできないんだよ、わかるかい？\n一番腹立たしいのは、こんな道具は船大工以外誰も必要としないってことさ。そして植民地で船大工は俺一人。 この盗人は誰にも売れやしないし、結局捨てるだけだろう。あんたが盗人を探してみるとか、 町で聞き込みしてみてくれないか？俺は造船所を離れる暇がないんだ――急ぎの特別注文を仕上げなきゃならなくてね。";
					link.l1 = "よし、やってみるぜ。で、あんたの……その装置ってどんな見た目だったんだ？";
					link.l1.go = "Device";
					link.l2 = "俺には興味ねえな。";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "そんなものは俺にはねえ。";
			link.l1 = "おっしゃる通りです。";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "素晴らしい！こんなに早くやってくれて本当に嬉しいよ。その船はどこだ？";
			link.l1 = "今のところ、その船は停泊地にいる；名前は『"+pchar.GenQuest.Findship.Shipyarder.ShipName+"「。」";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "ほら、金だ― "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+"。仕事を引き受けてくれてありがとう。また必ず会いに来てくれよ。じゃあな！";
			link.l1 = "「さようなら。」 "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "もちろん、できるだけわかりやすく説明してみるぜ。どうやら "+pchar.GenQuest.Device.Shipyarder.Describe+"。それは唯一無二の品だから、すぐに分かるはずだ。その楽器を俺のところに持ってきてくれたら、 たっぷり報酬を払うぜ。";
			link.l1 = "了解だ。すぐに捜索を始めるぜ！";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "やったな！どれほど感謝しているか、君には分からないよ！もう二度と自分の楽器に会えないと、 すっかり諦めていたんだ。";
			link.l1 = "「はい、どうぞ。」";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "お前の働きに対して、報酬を払うぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+"。それがふさわしい報酬になるといいんだが。";
			link.l1 = "ありがとう！";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "それに加えて、感謝のしるしとして、あなたに一つ提案をしたいんだ。";
				link.l1 = "それは面白いな。まあ、やってみろよ――俺は嬉しい驚きってやつが好きなんだ。";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "新しい船を進水させたばかりだ―― "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Name")+"Acc"))+"。すでにこの船に興味を持っている客が何人かいるが、あんたを優先してやるぜ。もしこの船が気に入って、 値段にビビらねえなら、買うこともできるぞ。";
			link.l1 = "へっ！もちろん、見てみようぜ！";
			link.l1.go = "Device_complete_4";
			link.l2 = "ありがとう。でも今の船で十分満足してるし、乗り換えるつもりはねえよ。";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "まあ、好きにしな。改めて礼を言うぜ――幸運を祈る！";
			link.l1 = "お前にも幸運を祈るぜ！";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "見せてくれ……いや、そんな奴はいなかったな。その件については港長に聞いてみるといいぜ。";
				link.l1 = "もちろん……";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "いや、そうは思わねえな……";
				link.l1.go = "exit";
				link.l2 = "ありがとうございます。 "+GetFullName(NPChar)+"！どうかご友人によろしくお伝えください。";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "俺はちゃんと聞いてるぜ。";
			link.l1 = "逃亡者を連れてきたぜ。";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "ああ、船長、本当にありがとうございます！彼女はどうですか？怪我はしていませんか？なぜ逃げたんです？ なぜなんです？\n彼女には分からないんでしょうか？花婿は裕福で地位のある男なんですよ！若さというものは、無知で愚か……時には残酷です。覚えておいてください！";
			link.l1 = "まあ、あなたは彼女の父親で最終的な決定はあなたのものですが、結婚を急ぐのはやめたほうがいいでしょう…";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "何が分かるんだ？お前に自分の子供はいるのか？いないのか？子供ができたら俺のところに来い、そしたら話をしよう。\n彼女を家族の元に連れ戻してくれた者には報酬を約束したんだ。";
			link.l1 = "ありがとう。あの娘には気をつけたほうがいいぜ。俺の勘だが、あれで終わるとは思えねえからな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "おや、あなたが私の放蕩息子に若い花嫁を連れてきた船長か？";
				link.l1 = "ああ、俺だ。";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "おう、そこの "+GetSexPhrase("彼は、我々の恩人だ","彼女こそ、我々の恩人だ")+"。報酬を期待してるんだろう？";
				link.l1 = "まあ、報酬なんていらねえよ、旦那の感謝の言葉だけで十分だ。";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "困難な状況で私の子供を見捨てず、繊細な問題から救い出してくださったこと、心より感謝いたします。\nどうか私からのささやかな金銭と贈り物をお受け取りいただき、感謝の気持ちをお伝えさせてください。";
			link.l1 = "ありがとうございます。この若い二人を助けることができて嬉しかったです。";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感謝だと？何が感謝だ！？あの間抜けが仕事もせずに半年もぶらぶらしてるってのに――しかも、色恋沙汰にうつつを抜かす暇はあるらしいじゃねえか！俺があいつの年の頃には、 もう自分の商売を切り盛りしてたぜ！ふん！総督には嫁入り前の娘がいるってのに、 あの馬鹿は身寄りもない女をうちに連れてきて、俺に祝福を頼むなんてよくもまあぬけぬけと言えたもんだ！";
			link.l1 = "ふむ……どうやら本当の気持ちなんて信じてないんだな？";
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
			dialog.text = "何の感情だ？どんな感情のことを言っているんだ？感情だと…お前の年でそんなに軽率でいられるとはな！若い者の気まぐれに付き合い、世話役のように振る舞うとは恥を知れ！ お前は娘を家から連れ出しただけでなく、俺の新米の人生まで台無しにしたんだ。お前に感謝などしない。じゃあな。";
			link.l1 = "ああ、そっちも同じようにな…";
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
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("冗談じゃねえだろうな？お前の船はどこだ？港に見当たらねえぞ！","悪魔に誓って言うが、俺を騙そうったってそうはいかねえ！お前の船は港にいねえぞ！"),pcharrepphrase("港にあなたの船が見当たらないな、船長 "+GetFullName(pchar)+"。あの船が「フライング・ダッチマン」じゃなければいいんだが？","船長、桟橋から積荷を積む方がずっと楽ですよ。船を港に入れて、また来てください。"));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"なんて面倒なんだ！よし、ずる賢いじじい、またすぐ会おうぜ！","「あなたを騙すつもりはなかった」 "+GetFullName(npchar)+"、島の向こう側に船がある。"),pcharrepphrase("いいや。俺の船は『ブラックパール』ってんだ！\nどうした、その顔は？青白いぞ……ははっ！冗談だよ！","助言ありがとう、必ずそうするよ。"));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("冗談じゃねえだろうな？お前の船はどこだ？港に見当たらねえぞ！","悪魔に誓って言うが、俺は騙されねえぞ！お前の船は港にいねえ！"),pcharrepphrase("港にあなたの船が見当たらないな、船長 "+GetFullName(pchar)+"。あれが「フライング・ダッチマン」じゃなければいいが？","船長、桟橋から積荷を積む方がずっと楽ですよ。船を港に入れて、また来てください。"));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"面倒くせえな！よし、ずる賢いじじい、またすぐ会おうぜ！","「あなたを騙すつもりはなかった」 "+GetFullName(npchar)+"「島の向こう側に船があるぞ。」"),pcharrepphrase("いや、俺の船は『ブラックパール』って名前だぜ！\n顔どうしたんだ？真っ青じゃねえか……ははっ！冗談だよ！","助言ありがとう、必ずそうするぜ。"));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "帆の色を変えるには費用がかかる "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+"、紋章を変更するには費用がかかる "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+"、帆の交換はお前さんの船によるぜ。";
							  
			    link.l1 = "新しい色を選んでくれ。";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "新しい紋章を描いてくれ。";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "特別な帆を取り付ける。"; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "考えが変わった。";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("冗談じゃねえだろうな？お前の船はどこだ？港に見当たらねえぞ！","悪魔に誓っても、俺は騙されねえぞ！お前の船は港にいねえじゃねえか！"),pcharrepphrase("港にあなたの船が見当たらないな、船長 "+GetFullName(pchar)+"。あの船が「フライング・ダッチマン」じゃなければいいが？","船長、桟橋から荷物を積み込む方がずっと楽ですよ。船を港に着けて、また来てください。"));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"なんて面倒だ！よし、ずる賢い爺さん、またすぐ会おうぜ！","「あなたを騙すつもりはなかった」 "+GetFullName(npchar)+"、島の向こう側に船がある。"),pcharrepphrase("いや、俺の船は『ブラックパール』って名前だ！\nどうしたんだ、その顔色は？真っ青じゃねえか……ハハッ！冗談だよ！","助言ありがとう、必ずそうするよ。"));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "どの帆を取り付けたいんだ？今はお前が持っているのは "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "取り付けたい "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "取り付けたい "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "取り付けたい "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "取り付けたい "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "取り付けたい "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "取り付けたい "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "気が変わった。";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "現在、あなたは持っている "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+"、あなたが選択した "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+"。交換の費用は "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+"。進めるか？";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "ああ。";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "いいや。";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "素晴らしい！すべてうまくいくさ。";
		    Link.l9 = "ありがとう。";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "どの色にする？値段は "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "考えが変わった。";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "金が用意できたらまた来てくれ。";
			    Link.l9 = "いいだろう。";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "承知した。帆を塗り替えるぞ "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" 色。";
		    Link.l9 = "ありがとう。";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "残念ながら、あなたの船には紋章を掲げることはできません。";
				    Link.l9 = "残念だな。";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "金が用意できたらまた来い。";
			    Link.l9 = "いいだろう。";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "申し訳ないが、旦那、今は売りに出せる船は一隻もないんだ。";
			link.l1 = "それは本当におかしいな。あんたの造船所に新品のラガーがあるって聞いたんだが。";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "ああ、たぶんミシェル・ド・モンペールが三千ペソの保証金を出したラガー船の件だろう？その船なら、もう売却済みだ。 契約書によれば、進水後一週間以内に全額を支払うことになっていたからな。\n期限はすべて過ぎたし、金も受け取っていない。だからラガー船は売ったんだ。申し訳ない、旦那。";
				link.l1 = "ああ、本当に運が悪かったな……。でも、他に売り物の船は本当にないのか？";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "ふむ。確かにそうだ。しかし……";
			link.l1 = "それに、すでに手付金が入っているんだ――五千ペソさ。金を預けたミシェル・ド・モンペールが、この船に関するすべての権利を俺に譲ったんだ。";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "You only have "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "そういうことなら、話を続けよう、旦那。ご指摘の通り、船のための五千ペソの手付金は確かに受け取った。だが、 弾薬を含めた船の全額は一万五千ペソだと思っている。だから、あと一万ペソ払ってくれれば船はあんたのものだ。\n契約によれば、船の進水から一週間以内にその金を支払わなければならない。"+sTemp+"、それから俺はこの船を他の客に売る自由があるんだぜ。しかもな、もう買い手がいるから、急いだほうがいいぞ。";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "急ぐ必要はない。今、必要な金額は手元にある。ほら、どうぞ。";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "わかった、わかった。金はちゃんと払うよ、旦那。あんたを長く待たせたりしねえ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "何かご用ですか、旦那？";
				Link.l1 = "ちょっと立ち寄って、おたくの船を見せてもらおうと思ったんだが……今は少し忙しくてな、片付けなきゃならねえ用事があるんだ。終わり次第、また戻ってくるぜ。";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "旦那、三日間しか猶予がないと警告したはずです。その期限は切れましたし、あなたは結局金を持ってこなかった。 だから取引は無効になり、船は他の客に売りました。悪く思わないでください。";
					link.l1 = "ああ、本当に運が悪かったな……。だが、他に売りに出してる船は本当にないのか？";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "一万持ってきたかい、旦那？";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "ああ、持ってるぜ。ほらよ。";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "いや、まだ作業中だ。";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "それでは、この素晴らしい購入をお祝い申し上げます。船はあなたのものです。 どうかこの船があなたにとって良き相棒となりますように。";
			link.l1 = "ありがとう！";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = GetShipName("Adeline");
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "ふむ……実は一つあるにはあるんだが、あんたに合うかどうかは分からねえな。";
					link.l1 = "まあ、今はあまり贅沢も言ってられねえな。持ってるものを見せてくれ！";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "聞けよ、旦那、まずは金を積んでから船のことを聞け、いいな？ここじゃタダで何かもらえると思うなよ。わかったか？";
					link.l1 = "よくわかったよ、そんなに無礼にすることはなかっただろうが。\nわかった、金が用意できたらまた来るぜ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "じゃあ、見てくれ。最近、手頃な値段でスループを買ったんだ。元は海賊船で、前の持ち主たちは数々 の罪で既に無事に絞首刑になった。正直言って、この船はラガーよりも出来が悪いし、損傷もひどいが、 まだ海に出すことはできる。\n今は修理する暇がない――うちの連中はみんな、注文されたブリッグの建造で手一杯だからな。だから、このままの状態で俺から買ってくれていい。 その分、普段より安く売るし、さらに船倉の中身――一万五千ペソ分も付けてやるぜ。";
			link.l1 = "いいだろう。船が航海に耐えればそれで十分だ。グアドループはすぐ近くだし、もしお前に手が回らなくても、 あそこで修理してもらうさ。";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "それでは、この素晴らしい購入をお祝い申し上げます。\n船はあなたのものです。\nどうかこの船があなたの役に立ちますように。";
			link.l1 = "ありがとう！";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "さて、旦那、金を持って戻ってきたのか？";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "ああ、みすぼらしい船くらいなら買えるだけの金はあると思うぜ。";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "まだ足りねえな。ちょっと様子を見に寄っただけだ…";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "ああ、友よ、俺たち二人ともここでひどい目に遭ったな。樹脂は没収され、俺は保釈金に莫大な金を無駄にした。 だが一体どうやってあいつらは俺たちの取引を嗅ぎつけたんだ？きっと俺の作業員の誰かだろう……この件は俺が片付ける。罪ある者に神の慈悲を！";
			link.l1 = "「つまり、俺の努力は全部無駄だったってことか……」";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "申し訳ありません、船長。ここではどうにもできません、運命ってのは時にひでえもんですぜ。";
			link.l1 = "なるほど。わかった、じゃあ俺はこれで失礼するぜ。さらばだ！";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "その話に戻りたいんだ。もしあんたが余分な絹を用意してくれるなら……船の修理や作業について、かなり大きな値引きをしてやってもいいぜ……いや、本当に相当な割引だぞ……";
			link.l1 = "旦那、早速本題に入りましょう。俺はスパイでもなければ、ドイル大佐の手下でもありません。それに、 マーカス・タイレックスと組んでいます――その名はご存知のはずです。だから、腹を割って話しましょう。 旦那が絹の帆布を安定して仕入れたいのは知っていますし、マーカス・タイレックスもそれを定期的に届けるつもりです。 ただし、値段で合意できればの話です。では、その話に移りましょうか、旦那？";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "わかった。どうやら俺には選択肢がないようだ――お前がドイルの手先で俺を牢屋に送り込むか、急いで大量の絹を見つけなければ俺は破産だ。25ドゥブロンで一反につき払う用意はあるが、大口の取引だけだ、100反未満は受け付けないぞ。";
			link.l1 = "それでは取引成立だな。タイレックスが毎月100巻の出荷を用意できるはずだ。";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "それは素晴らしい！すぐに最初のロットを購入できるぞ。";
			link.l1 = "今はできねえが、時間はかからねえぜ。あんたが欲しい貨物を積んだ船が今カプスタービルにいるから、 すぐに向かってそいつをあんたのところに送る。\n荷下ろしはどこでやるんだ？";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "こうしよう。毎月10日から15日の夜、俺の部下が湾で……いや、待て、やっぱりネグリル岬でお前の使者を待つことにする。\n距離はかなりあるが、巡回はずっと少ない……合言葉は「リヨンの商人」だ。";
			link.l1 = "承知したぜ、旦那。すぐにキャップスターヴィルへ向かう。";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "お前の船が早く到着してくれればいいんだが、新しい絹が切実に必要なんだ。";
			link.l1 = "心配するな、すべてうまくいくさ。幸運を祈るぜ！";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "いいや "+pchar.name+"。俺はあんたに恨みはねえが、まずは俺の国との問題を片付けてくれ。王冠の敵にこんな貴重な品を売ったら、 誤解されかねねえからな。";
					link.l1 = "ああ、そして出所不明の品を船に積み込むときは親友ってわけか？この誤解を俺がちゃんと片付けてやるから待ってな。";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "そうだな。なぜだ？何か造ってるのか？";
					link.l1 = "いや、俺は特別な依頼で来てるんだ。プランテーションの管理人のためにな。";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "俺にはどうにもできねえ。";
				link.l1 = "残念だな！";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "なるほど。この管理人が十分に用意してくれたことを願うよ、こんなセットなら俺ならかなり高く取るところだぜ。 最近本国からの輸入品があったのは運が良かったな。";
			link.l1 = "いくらだ？";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "千枚の金のドゥブロンだ。";
			link.l1 = "熱くなってるな。俺は大丈夫だ。引き受けるぜ。";
			link.l1.go = "IslaMona_7";
			link.l2 = "高すぎるな。俺みたいに全部まとめて買う奴なんて他にいねえだろう。いくつかは売れるだろうが、 残りは地元の浮浪者どもに盗まれるだけさ。少し値引きしてくれないか？\n";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = "必ず見つかると保証するぜ。値段は変わらねえ。どうだ？あまり長くは待たねえぞ。";
				link.l1 = "わかった、わかったよ。買わせてもらうぜ。";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "よし、百でいこう。九百だ。それ以下にはしねえ。頼むからそれ以上言うな。";
				link.l1 = "俺はやらねえよ。賛成だ。";
				link.l1.go = "IslaMona_7";
				link.l2 = "もっとくれないか？卸売りとしてさ。そしたら修理と塗装もお前に頼むし、一番イカした船首像も注文するぜ。";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				Notification_Skill(false, 85, SKILL_COMMERCE);
				dialog.text = "生きた女を注文しようが俺の知ったこっちゃねえ。九百だ。";
				link.l1 = "わかった、わかったよ。買わせてもらうぜ。";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "本当に大丈夫か？忘れたりしねえだろうな？よし、もう百だけ切ってやる。だが、これで最後だぞ！";
				link.l1 = "忘れねえぜ。約束だ！";
				link.l1.go = "IslaMona_7";
				link.l2 = "「そうだな、どう言えばいいか……」";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "考えられねえ！ "+pchar.name+"、頭に鉛玉が残ったままなのか？サソリみてえに欲深い野郎だな！最近のお前の悪事はみんな知ってるぜ！ もうたんまり金を稼いだんだろ、他の奴らが稼ぐのを邪魔すんじゃねえ。一言でも余計なこと言ったら、 千枚以下じゃ売らねえからな。";
			link.l1 = "わかった、わかった！落ち着けよ。俺も同意するぜ。";
			link.l1.go = "IslaMona_7";
			link.l2 = "しかし、 "+npchar.name+"「俺には小さな子供たちがいるんだ！あいつらのことも考えなきゃならねえ！正直な運送じゃ大して稼げねえって、 あんたも分かってるだろう！」";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				Notification_Skill(false, 100, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "「娼婦の子供なんざ数に入らねえ」 "+pchar.name+"……お前にはうんざりだ。樽の上にドブロン金貨千枚置け、さもなきゃおさらばだぜ。";
				link.l1 = "どういう意味だ、違うって？ふん。そうだな、お前は詐欺師だ。";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "子供がいるなんて知らなかったぜ。それに、そんなに状況が悪いとはな。わかった、不満は言うな。七百だ。 ほとんど損みたいなもんだぜ。";
				link.l1 = "忘れねえぜ。約束だ！";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "つまり、俺に借りができたな "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" ドゥブロン金貨。";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "ほら、これで最後だ、もう何も残っちゃいねえ。";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (PCharDublonsTotal() < 1)
				{
					link.l1 = "待ってくれ、これから高利貸しのところへ行って借金してくるぜ。";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "今持ってるのはこれだけだ "+FindRussianDublonString(GetCharacterItem(pchar,"gold_dublon"))+"。これを受け取れ、俺は高利貸しのところへ行ってくる。";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
            dialog.text = "俺に同情なんかするなよ、お前の船室のロッカーは金でいっぱいだろ。借りがあるんだぜ "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "それは素晴らしい。全額揃っているな。道具はお前の船に届けるぜ。重い木箱だからな。";
			link.l1 = "ありがとうございます。 "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}

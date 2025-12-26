#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		PortmanDelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		if(CheckAttribute(chref, "DontNullShip"))
		{
			DeleteAttribute(chref, "DontNullShip");
			DeleteAttribute(NPChar, "DontNullShipBeliz");
		}
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
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
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verildi ve şimdi herkes seni arıyor. Senin yerinde olsam orada kalmazdım.","Şehirdeki tüm muhafızlar seni arıyor. Seninle konuşacak kadar aptal değilim!","Koş, "+GetSexPhrase("dostum","lass")+", askerler seni delik deşik etmeden önce..."),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("serseri","pislik")+"?! Şehir muhafızları kokunu çoktan aldı, fazla uzağa gidemezsin, pis korsan!","Katil, hemen evimden çık! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("alçak","sıçan")+"! Yakında seni kalemizde asacaklar, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun değildir...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", ve belki de o pis dilini koparmam!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ve oradaki herkes - korsanları yakalayın! Sana söylüyorum dostum: sessiz kalırsan hayatta kalırsın..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Ah, seni tanıyorum. Yükü teslim etmen gerekiyordu ama çalıp götürdün! Muhafızlar, muhafızlar!";
					Link.l1 = "Aaargh!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "Size nasıl yardımcı olabilirim, monsieur?";
				Link.l1 = "Sizinle bir işim var...";
				Link.l1.go = "quests";
				Link.l2 = "Üzgünüm, ama gitmem gerekiyor.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Selamlar, "+GetAddress_Form(NPChar)+". Sanırım daha önce tanışmadık. Ben "+GetFullName(npchar)+" - liman şefi.";
				Link.l1 = "Merhaba, "+GetFullName(NPChar)+". Ben "+GetFullName(PChar)+",   '   gemisinin kaptanı"+PChar.ship.name+"'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "Kaptan MacArthur, her zaman hatırlattığım gibi - her seferinde bana uğramana gerek yok. Merak etme.";
					link.l1 = "Yeter artık, Bayım "+npchar.lastname+" Ben de herkes gibiyim.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Selamlar, "+GetAddress_Form(NPChar)+" . Benimle bir işiniz mi var?","Merhaba, "+GetFullName(Pchar)+". Gemimizi limanımıza girerken gördüm ve beni görmeye geleceğinden emindim.","Ah, kaptan "+GetFullName(Pchar)+". Seni buraya getiren nedir?");
				Link.l1 = "Merhaba, "+GetFullName(NPChar)+". Seninle konuşmak istiyordum.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Peki, parayla ilgili durum nedir? Bana en azından bin peso getirdin mi?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Evet, var"+GetSexPhrase("","")+". Tam olarak bin peso. Şimdi, bilgi!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Hayır, henüz değil...","Henüz değil...","Henüz değil, ama yakında getireceğim...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Lütfen, sorunun özünü açıklamama izin verin. Eski dostum, Kaptan  "+PChar.GenQuest.ChurchQuest_1.CapFullName+", birbirimizi sadece birkaç saatle kaçırmışız ve onunla acil bir işim var. Şimdi ona yetişmem gerekecek, ama hiçbir fikrim yok"+GetSexPhrase("","")+" nerede olduğuna dair.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Liman müdürü, efendim, ' adlı gemi hakkında biraz bilgiye ihtiyacım var"+PChar.GenQuest.ChurchQuest_1.CapShipName+" kaptanın sahip olduğu "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Koloniniz için olan yük gemimin ambarında.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Koloniniz için olan yük gemimin ambarında.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Ah, sonunda geldiniz demek. Açıkçası, geri döneceğinizi beklemiyordum. Sizi aranan kişi olarak kayda geçmeleri için yetkililere çoktan başvurduk. Peki, söyleyecek bir şeyiniz var mı?";
						Link.l1 = "Beklenmedik koşullar nedeniyle yükü zamanında teslim edemedim. Ama bu sorunu barışçıl bir şekilde çözmek istiyorum. Yükünüzü getirdim ve umarım bir anlaşmaya varabiliriz.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Ah, seni tanıyorum. Yükü teslim etmen gerekiyordu ama çalıp kaçtın! Muhafızlar, muhafızlar!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Sizin koloninize posta teslim ettim.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ah, sonunda geldiniz demek. Açıkçası, artık öldüğünüzü düşünmeye başlamıştık... Neyse, en azından bir aptal olmanız, ölü olmanızdan iyidir sanırım.";
					Link.l1 = "Beklenmedik olaylar yüzünden postayı zamanında ulaştıramadım. Ama işte burada.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Ne oldu? Ölümden dönmüş gibisin.";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+", beni tehlike konusunda uyardığında haklıydın. Liman idaresi ofisinin hemen dışında siyahlar giymiş iki adam bana saldırdı ve... paketi elimden aldılar.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Liman müdürü tarafından buraya gönderildim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Bana silah ve cephane taşıyan bir gemiye eşlik etmem söylendi. İşte belgelerim.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Silahlarla dolu gemiye, anlaştığımız gibi eşlik ettim.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Kayıp gemiyi buldum ve limanınıza getirdim. Geminin kaptanı size çoktan rapor vermiş olmalı.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Kayıp gemiyi buldum ve limanınıza getirdim. Geminin kaptanı zaten size rapor vermiş olmalı.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Kayıp gemiyi adanın kıyılarında buldum "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+" .  Gemisinin kaptanı, ezici korsan kuvvetlerine karşı umutsuz bir mücadeleye girişmişti. Elimden gelen her şekilde yardım ettim ama ne yazık ki boşunaydı: o alçak herifler gemiyi batırdı. O noktada yapabildiğim tek şey onun intikamını almaktı.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Kaybolan gemiyi adanın kıyılarında buldum "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Aslında gemi değil, ama mürettebatından yaklaşık elli kişi ve kaptanı hakkında. Şimdi güvendeler - mürettebat benim gemime bindi, kaptan ise şu anda kasabanızda - sanırım size çoktan uğradı.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Verdiğiniz görevi yerine getirdim. Ticaret konvoyuna saldıran korsan filosu yok edildi.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Koruma gemisinin kaptanıyım. Ticaret gemilerini limana getirdiğimi bildirmek için geldim.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Ben eskort gemisinin kaptanıyım. İki ticaret gemisini ve yüklerini limana getirmekle görevlendirildim, fakat ne yazık ki, koruduğum iki gemi de düşman konvoyuyla yapılan bir savaş sırasında battı. Yine de yükü teslim etmeyi başardım.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
					Link.l1 = "Ben eskort gemisinin kaptanıyım. Ticaret gemilerini limana getirdiğimi bildirmek için geldim.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Bunu söylediğinizi duymak ne hoş. Sizin yerinizde olan çoğu kişi kendini beğenmiş olurdu. Peki, ben ve kayıtlarım size nasıl yardımcı olabiliriz?";
			}
			else dialog.text = "Mükemmel. Hizmetinizdeyim, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Alabileceğim bir işiniz var mı? Ya da belki bir kontrat?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Gemilerimden birini burada bir süreliğine demirleyebilir miyim?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Gemimi geri almak istiyorum.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Mali konuları konuşmaya geldim.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ben buraya belli bir adamın isteği üzerine geldim. Adı Vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+"     beni sana gönderdi. Bir şey almam gerekiyormuş...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Liman otoritenize kayıtlı kaptanlar hakkında daha fazla bilgi almak isterim.";
			link.l6.go = "CapitainList";
			link.l61 = "Benzersiz, özel yapım gemiler ve efsanevi kaptanları hakkında herhangi bir bilginiz var mı?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Başka bir işle ilgileniyorum.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Merhaba, oğlunuzun daveti üzerine geldim."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Bu, kızınızla ilgili...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Bu gemi belgelerinin bulunduğu paketi tesadüfen buldum.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Bu gemi belgelerinin bulunduğu paketi tesadüfen buldum, birisi kaybetmiş olmalı.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Teşekkür ederim. Hoşça kal.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Senin sorunun kolayca çözülebilir. Seyir hizmetleri yetkilisine git, o sana arkadaşının gemisinin rotasıyla ilgili tüm bilgileri verebilir.";
			link.l1 = "Ne yazık ki, o kadar basit değil. Arkadaşım gemisinin adını sizin limanınızda değiştirdi... dini sebeplerden dolayı.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Anladım. Bu işleri biraz daha karmaşık hale getiriyor. Gemi sicilindeki kayıtlara göz atmam gerekecek, bu da biraz zaman alacak. Zamanın para olduğunu muhtemelen biliyorsunuzdur.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Bunu tamamen anlıyorum, efendim "+GetFullName(NPChar)+", ve zamanınızı değerlendirmek için yeterince hazırım ... diyelim ki, bin peso tutarında.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Ne yazık ki, şu anda yanımda hiç param yok... Sonra tekrar uğrarım...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Mükemmel! Şimdi bakalım... bir dakika... işte... tamam. Geminin yeni adı kaydedildi, ve bundan böyle gemi ' olarak bilinecek."+PChar.GenQuest.ChurchQuest_1.CapShipName+"'  Kaptan [[[VAR0]]] komutasında "+PChar.GenQuest.ChurchQuest_1.CapFullName+" bugün   doğru yelken açtı "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh! Gerçekten de ne kadar meşgul bir adam olduğumu anladınız, bunu takdir etmenize sevindim! Şimdi bakalım... bir dakika... işte... tamam. Gemi isminin değiştirilmesi kayıtlara geçti ve bundan böyle gemi şu isimle anılacak: '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"'  Kaptan [[[VAR0]]] komutasındaki  "+PChar.GenQuest.ChurchQuest_1.CapFullName+" bugün  yelken açtı "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "Teşekkür ederim efendim, bana büyük bir iyilik yaptınız.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Tam olarak ne bilmek istiyorsun?";
			link.l1 = "Şu kaptanın sahip olduğu geminin limanınızı ziyaret edip etmediğini söyleyebilir misiniz?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... Ve neden sorduğunuzu öğrenebilir miyim?";
			link.l1 = "Onunla bir işim var. Ama eğer limanınıza uğramadıysa ya da onu tanımıyorsanız...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Yaptı. Ama tüm Azizlere şükürler olsun ki, tam bu sabah buradan ayrıldı ve gitti "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+". Ve onunla uğraşmak zorunda kalan herkese gerçekten acıyorum.";
			link.l1 = "Öyleyse bana şans dile – ve yardımın için teşekkür ederim.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Ne bilmek istiyorsun, "+GetSexPhrase("bayım","miss")+" "+GetFullName(PChar)+"?";
			link.l1 = "Bu kaptanın limanınıza uğrayıp uğramadığını bana söyleyebilir misiniz?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, gerçekten de öyle yaptı. Ve şunu söylemeliyim ki, nihayet bu çok çekmiş limandan ayrılacağı o kutsanmış anı sabırsızlıkla bekliyorum.";
			link.l1 = "Yani gemisi hâlâ burada mı?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Evet, efendim "+GetSexPhrase("efendim","hanımefendi")+". Limandaki en alt kademedeki yükçüsünden, kılavuzluk hizmetinin başına kadar herkes onun bir an önce gitmesi için dua ediyor. Gemisi daha yeni kuru havuzdan çıktı, hemen tamir edildi, ama o zamana kadar cesur kaptanımız limandaki tüm marangozlarla kavga etmiş ve geminin gövdesi için seçilen üç parti keresteyi reddetmişti bile. Ama yarın, en yüce ve her şeyi gören Rabbimiz bizi ondan... o baş belası, herkesin canını sıkan o dertten kurtaracak!";
			link.l1 = "Sakin olun, efendim "+NPChar.Name+", ve unutma ki bir başkası için bu sınav daha da zor olacak. Sen bu sınavı çoktan geçtin, ama ben henüz o kaptanını tanımadım. Şimdi, müsaadenle...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Bir bakayım! Evet, gerçekten de belgelerimde bu set geçersiz olarak işaretlenmiş. Bana uğrayıp bu evrakları teslim ettiğiniz için çok naziksiniz. Rüzgarınız bol olsun, kaptan!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go unrewarded.  ";
			dialog.text = s1+"Söylesene, şu miktarı düşünür müsün "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" peso, bu ödül uygun mu?";
			link.l1 = "Tabii ki hayır!";
			link.l1.go = "exit";
			link.l2 = "Pekala, mütevazı bir meblağ, ama zaten öyle büyük bir iş de değildi. Evet, teklifinizi kabul ediyorum, "+npchar.name+".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Teklifimi kabul edecek misiniz?";
			link.l1 = "Tabii ki hayır!";
			link.l1.go = "exit";
			link.l2 = "Belki. Ama eminim bu belgeler çok daha değerli.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Tamamen dinliyorum.";
			link.l1 = "Kaçağınızı getirdim.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ah kaptan, çok teşekkür ederim! Nasıl, iyi mi? Yaralandı mı? Neden kaçtı? Neden?\nAnlamıyor mu? Damat zengin ve önemli bir adam! Gençlik saf ve düşüncesiz olur... hatta acımasız. Bunu unutmayın!";
			link.l1 = "Sonuçta onun babasısınız ve son karar size ait, ama ben bu evliliğe aceleyle karar vermenizi tavsiye etmem...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Ne biliyorsun ki? Senin de çocuğun var mı? Yok mu? Bir gün olursa, gel yanıma, o zaman konuşuruz.\nOnu ailesine geri getiren herkese bir ödül vadettim.";
			link.l1 = "Teşekkürler. Ona göz kulak olmalısın. İçimde bir his var, bununla yetinmeyecek gibi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, demek sen o kişisin "+GetSexPhrase("getiren kaptan","getiren genç hanım")+"   genç bir gelinle kayıp oğlum mu?";
				link.l1 = "Evet, kaçmalarına yardım ettim.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Haydi ama, iyiliksever dostum. Bir ödül mü bekliyorsunuz?";
				link.l1 = "Pekâlâ, ödül istemem, minnettarlığınız bana yeter.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Çocuğumu zor durumda bırakmadığınız ve o hassas durumdan çıkmasına yardımcı olduğunuz için size çok minnettarım. Size teşekkür etmeme izin verin, lütfen bu mütevazı meblağı ve şahsi hediyemi kabul edin.";
			link.l1 = "Teşekkür ederim. Bu genç çifte yardımcı olmak benim için bir zevkti.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Teşekkür mü? Ne teşekkürü?! O sersem yarım yıldır işsiz güçsüz dolaşıyor – bir de bak hele, aşk meşk işlerine vakti var! Ben onun yaşındayken kendi işimi kurmuştum! Pöh! Vali evlendirecek kız arıyor – bu ahmak ise köksüz, kimliksiz bir kadını evime getirdi, bir de utanmadan hayır duamı istedi!";
			link.l1 = "Hmm... Görünen o ki, gerçek duygulara inanmıyorsun?";
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
			dialog.text = "Ne hisleri? Hangi hislerden bahsediyorsun? Hisler... senin yaşında insan nasıl bu kadar düşüncesiz olabilir?! Gençlerin heveslerine boyun eğip onları şımartmak, üstüne bir de aracılık yapmak sana hiç yakışmadı! Sadece bir kızı evinden almakla kalmadın, acemimin de hayatını mahvettin. Senden bir teşekkür bekleme. Elveda.";
			link.l1 = "Peki, sana da aynı şekilde...";
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
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Evet, kahretsin! Sana bir işim var!","Ha! Tam zamanında geldiniz! Çözülmesi gereken bir meselem var.","Elbette! Tabii ki senin için bir işim var! Son zamanlarda sorunlardan başımı kaldıramıyorum...");
				link.l1 = "O halde lütfen sadede gelin, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Tanrım! Kaptan "+GetFullName(PChar)+", tam zamanında geldiniz! Ne talihsizlik, ne büyük bir felaket... Liman yetkililerinin gözetimindeyken gemi rıhtımda yandı! Güvenliğin dikkatsizliği yüzünden gemi yandı... su hattına kadar kül oldu...\n"+"Tanrım, böyle bir cezayı hak etmek için ne yaptım? Yıllardır sadık bir hizmetkâr oldum...";
				link.l1 = "Peki, mesele ne? Bir gemi yandı, ne olmuş? Sigorta sözleşmeleri ne işe yarıyor? Yoksa paranı korumak için sigorta yaptırmamaya karar verdin de şimdi pişman mı oldun?";
				link.l1.go = "BurntShip4";
				link.l2 = "Tersane bu konuda size benden daha iyi yardımcı olabilir. Birkaç ay içinde eskisini onaracaklar ya da yenisini inşa edecekler. Üzgünüm, ben bir gemi yapımcısı değilim...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Vali vatandaşlarının iyiliğini önemser, bu yüzden her zaman verecek işleri olur. Meyhanede yardım arayan tüccarlar olabilir, ayrıca dükkân da yük taşımak için kaptanlara ihtiyaç duyuyor.";
			Link.l1 = "Bir sorum daha var.";
			Link.l1.go = "node_2";
			Link.l2 = "Teşekkür ederim. Hoşça kal.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Kaptanı bulman gerekiyordu "+npchar.quest.PortmansJornal.capName+" ve gemi günlüğünü ona geri ver. Başardın mı?";
				link.l1 = "Hayır, henüz değil...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Çalınan bir şeyi bulmaya kendini adadın "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. O işi bitirene kadar sana başka görev verilmeyecek.";
				link.l1 = "Aramaya devam edeceğim, sadece bekle.";
				link.l1.go = "exit";
				link.l2 = " Görevi bırakmak istiyorum. ";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Bana çalınanı bulacağına söz vermiştin "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Yaptın mı?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Evet, buldum, şimdi limanda. Alabilirsin.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Aramaya devam edeceğim, sadece bekle.";
					link.l1.go = "exit";
				}
				link.l2 = "Bu görevi bırakmak istiyorum.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("   Bu bayrak altında yelken açanlara iş yok   "+NationNameGenitive(sti(pchar.nation))+"  Ofisimden derhal çık! ","Ben   ile işbirliği yapmayacağım "+NationNameAblative(sti(pchar.nation))+". Defol!");
						link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Peki, nasıl istersen...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "İtibarınız bana güven vermiyor. Sizinle iş birliği yapmayacağım. Hoşça kalın.";
						link.l1 = "Ne! Bunların hepsi yalan.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Sizi küçümsemek istemem kaptan, ama... Korkarım görevimi tamamlayamazsınız – açıkçası yeterli deneyiminiz yok. Sizinle bir sözleşme imzalayamam.";
						link.l1 = "Anladım. Peki, dediğiniz gibi olsun.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hmm... Eh, bu ilgilendiğiniz işe bağlı.";
					link.l1 = "Gemimi yük taşımacılığı için kiralayabilirim.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Tüccarları koruyarak fazladan para kazanmak istiyorum.";
					Link.l2.go = "escort_begin";	//эскорт
					link.l3 = "Posta teslim ederek ekstra para kazanmak istiyorum.";
					Link.l3.go = "cureer_begin";	//доставка почты
					Link.l4 = "Peki, belki siz de bir şey önerebilirsiniz?";
					Link.l4.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Bugünlük başka iş yok. Başka bir gün tekrar gel.";
					link.l1 = "Pekala.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Liman’da gemini göremiyorum. Açıkta bekle, sonra tekrar gel – senin için bir iş bulmaya çalışırız.";
				link.l1 = "Pekala, tam olarak öyle yapacağım.";
				link.l1.go = "exit";
			}
		break;
			
		case "escort_begin"://эскорт
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		
		if (hrand(5) > 1)
		{
			if (GetCompanionQuantity(pchar) < 3 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) 
			{
				if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) 
				{ // если заняты
					dialog.text = "Maalesef, sana bu tür bir şey sunamam. Birkaç gün sonra tekrar uğra.";
					link.l1 = "Pekala, tam olarak öyle yapacağım.";
					link.l1.go = "exit";
				} 
				else 
				{ // если не заняты
					if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) 
					{ // 2 уровень
						dialog.text = "Şimdiye kadar birkaç kez tüccar gemilerine başarıyla eşlik ettiniz. Sanırım size uygun bir görevim var.";
						link.l1 = "Tamamen sizi dinliyorum.";
						link.l1.go = "Escort_LevelUp";
					} 
					else 
					{ // 1 уровень
						if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
							dialog.text = "Sana özel bir işim var. Limanda iki ticaret gemisi var, çoktan yola çıkmış olmaları gerekiyordu. Mesele şu ki, onlara eşlik edecek gemi hasar aldı ve gerekli onarımlar için hâlâ bekliyor, bu yüzden yakın zamanda hareket edemeyecekler.\nSenin gemin bu iş için tam uygun - ayrıca ambarına ek yük de yüklemem gerekecek. Elbette, ödeme de iki katı olacak - hem yük taşımacılığı hem de koruma için.";
							link.l1 = "Ne ilginç bir teklif! Kabul ediyorum!";
							link.l1.go = "escort_bonus";
							link.l2 = "Teşekkür ederim, ama bu tarz işler bana göre değil.";
							link.l2.go = "exit";
						} 
						else 
						{ // просто эскорт
							dialog.text = "Sana özel bir işim var. Şu anda limanımızda iki ticaret gemisi demirlemiş durumda - onlara eşlik edecek birine ihtiyaçları var. Bu gemilere varış noktalarına kadar eşlik etme fırsatını sana sunuyorum. Kabul eder misin?";
							link.l1 = "İlginç bir teklif! Kabul ediyorum!";
							link.l1.go = "escort";
							link.l2 = "Teşekkür ederim, ama bu tarz işler bana göre değil.";
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Bir konvoyu korumak için neredeyse bir tartanla gelmişsin. Bu iş için gerçek ateş gücüne sahip bir gemi gerekir — bir savaşçı ya da bir akıncı.";
				link.l1 = "Tamam, anladım.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Maalesef, sana bu türden bir şey sunamam. Birkaç gün sonra tekrar uğra.";
			link.l1 = "Pekala, tam olarak öyle yapacağım.";
			link.l1.go = "exit";
		}
		break;
		
		case "cureer_begin"://доставка почты
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
		
		if (hrand(5) > 1)
		{
			if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)
			{
				if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp"))
				{ 
					// если заняты
					dialog.text = "Maalesef, sana bu türden bir iş sunamam. Birkaç gün sonra tekrar uğra.";
					link.l1 = "Pekala, tam olarak öyle yapacağım.";
					link.l1.go = "exit";
				} 
				else 
				{ 
					// если не заняты
					if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) 
					{ //если 2 уровень
						dialog.text = "Yani... Bildiğim kadarıyla şimdiye kadar birkaç kez kurye olarak çalıştınız ve bu işlerde oldukça başarılı oldunuz. Size vereceğim görevin de üstesinden gelebilirsiniz diye düşünüyorum.";
						link.l1 = "Tamamen dinliyorum, "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "Postcureer_LevelUp";
					} 
					else 
					{ // первый уровень
						dialog.text = "Hızlı bir geminiz var görüyorum. Size bir kurye işi teklif edebilirim – mektup ve ticari evrak taşıma işi.";
						link.l1 = "Bu ilginç. Katılıyorum. Nereye gitmem gerekiyor?";
						link.l1.go = "Postcureer";
						link.l2 = "Teşekkür ederim, ama bu tarz işler bana göre değil.";
						link.l2.go = "exit";
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Üzgünüm, ama sana verecek bir işim yok. Bu tür görevler çevik bir akıncı gemisi gerektirir. Seninkiyle yük taşımak daha iyi olur.";
				link.l1 = "Tamam, anladım.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Maalesef, sana bu türden bir şey sunamam. Birkaç gün sonra tekrar uğra.";
			link.l1 = "Peki, tam da bunu yapacağım.";
			link.l1.go = "exit";
		}
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Ama duydum ki geminiz zaten kiralanmış. Size daha fazla yük veremem. Önceden verdiğiniz taahhütleri yerine getirin.";
					link.l1 = "Evet, muhtemelen haklısın.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Ambarında çok az yer var. Yük taşımak için daha geniş bir gemiye ihtiyacım var. Mağazaya uğramanı öneririm – buradaki tüccar genellikle küçük yük partilerini taşımak için gemi kiralar.";
					link.l1 = "Anladım. Peki, nasıl isterseniz.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Şu anda uygun bir işim yok. Ama zaten birkaç başarılı teslimat yaptınız. Size özel olarak vermek istediğim bir iş var.";
					link.l1 = "Dinliyorum. Ne tür bir iş?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Pekala, size birkaç kiralama fırsatı sunabilirim.";
				link.l1 = "Öyleyse, bakalım...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Bugünlük başka yük kalmadı. Başka bir gün tekrar gel.";
				link.l1 = "Pekâlâ.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "Şu seçenekler mevcut:\n"+"yük "+GetGoodsNameAlt(iFrahtGoods1)+" tutarında "+FindRussianQtyString(iFrahtGoodsQty1)+"  kasabasına "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods2)+" tutarında "+FindRussianQtyString(iFrahtGoodsQty2)+"  kasabasına "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods3)+" miktarında "+FindRussianQtyString(iFrahtGoodsQty3)+"  kasabasına "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\nSeçiminiz nedir?";
				Link.l1 = "İkinci seçeneği tercih edeceğim - şu kasabaya kiralama yapacağım: "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" yüklü "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Üçüncü seçeneği seçeceğim - kasabaya bir izin belgesi alacağım "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" yüklü "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Üçüncü seçeneği seçeceğim - kasabaya bir izin belgesi alacağım "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" yüklü "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Aşağıdaki seçenekler mevcut:\n"+"kargo "+GetGoodsNameAlt(iFrahtGoods1)+" tutarında "+FindRussianQtyString(iFrahtGoodsQty1)+"  kasabasına "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\ncargo "+GetGoodsNameAlt(iFrahtGoods2)+" tutarında "+FindRussianQtyString(iFrahtGoodsQty2)+"  kasabasına "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", içinde "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nSeçiminiz nedir?";
				Link.l1 = "İlk seçeneği seçeceğim - kasabaya bir izin belgesi alacağım "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" yüklü "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "İkinci seçeneği seçeceğim - şehre bir imtiyaz belgesi alacağım "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" yüklü "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Maalesef, bana uygun bir şey yok.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Pekâlâ, harika! Gerekli belgeleri hazırlayacağım, sen de gemini yüklemeye hazırlayabilirsin.";
			link.l1 = "Elimden gelenin en iyisini yapacağım!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Harika, o halde! Gerekli belgeleri hazırlayacağım, sen de gemini yükleme için hazırlayabilirsin.";
			link.l1 = "Elimden gelenin en iyisini yapacağım!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Pekâlâ, harika! Gerekli evrakları hazırlayacağım, sen de gemini yüklemeye hazırlayabilirsin.";
			link.l1 = "Elimden gelenin en iyisini yapacağım!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Bakalım, o zaman. Bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iFrahtGoods)+" miktarında "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Ama gördüğüm kadarıyla, tüm yükü teslim etmemişsiniz - siz "+FindRussianQtyString(sti(amount))+" kısa.";
				link.l1 = "Bin köpekbalığı! Kesin o lanet farelerdir! Ama merak etme, "+GetAddress_FormToNPC(NPChar)+", eksik miktarı satın alacağım ve tüm partiyi teslim edeceğim.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Bakalım, o zaman. Bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iFrahtGoods)+" tutarında "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Doğru mu?";
			link.l1 = "Kesinlikle doğru, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Limanımızda geminizi göremiyorum. Demir atın ve sonra tekrar yanıma gelin - o zaman konuşuruz.";
			link.l1 = "Pekala, tam olarak öyle yapacağım.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Ama sen "+FindRussianDaysString(iTime)+" geç kaldınız. Bu yüzden taşıma ücretinizden kesinti yapmam gerekiyor. Sözleşmeye göre, geciktiğiniz her gün için toplam tutarın yüzde beşi kadar ceza uygulanıyor. Lütfen, paranızı alın "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", ve lütfen bundan sonra sözleşmeye sadık kalmaya çalış.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Yaptığınız iş için teşekkürler. Lütfen, ödemenizi alın - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Yükü teslim ettiniz mi? Güzel. Aslında, teslimatı yapmak için yükü kendimiz satın almak zorunda kaldık! Üstelik bu bize epey pahalıya mal oldu, bilginiz olsun. İtibarınızı yeniden kazanmak istiyorsanız, masraflarımızı karşılamalı ve ayrıca cezayı da ödemeniz gerekecek. Yüke gelince, onu sizde bırakıyoruz - artık ihtiyacımız yok.";
			link.l1 = "Evet, tabii ki. Ne kadar?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = " Malların üç katı fiyatı. Bu da toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "Bu epey yüklü bir meblağ. Ama iş iştir. Peki, paran burada.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Sen deli misin? Böyle fahiş bir meblağ istemek tam bir açgözlülük! Benden hiçbir şey alamazsın!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Akıllıca bir karar. Şimdi gerçekten ciddi biri olduğunu görebiliyorum. Sanırım gelecekte de birlikte çalışabiliriz.";
			link.l1 = "Teşekkür ederim, ama şimdi gitmem gerek.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Anladım... O halde, bir daha asla hiçbir liman yetkilisinin karşısına çıkmamalısın "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! Defol!";
			link.l1 = "Pek bir şey kaçırmamışımdır herhalde...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Acele et, alıcı geminin geldiğini zaten biliyor ve yükü için endişeleniyor.";
			link.l1 = "Öyleyse, daha fazla zaman kaybetmeyeceğim!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Bu paket,   şehrindeki liman yetkilisine teslim edilmeli "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", için "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", ve mümkün olan en kısa sürede. Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Kabul ediyorum!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hmm... Ama o tarafa gitmiyorum. Üzgünüm, ama reddetmek zorundayım.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Harika! Sana güveniyorum. İşte paket.";
			link.l1 = "Hemen yelken açacağım!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Ama sen "+FindRussianDaysString(iTime)+" geç kaldınız. Bu yüzden iş için ödemenizi azaltmak zorundayım. Sözleşmeye göre, gecikilen her gün için toplam tutarın yüzde beşi kadar ceza uygulanıyor. Şimdi lütfen, alın "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", ve gelecekte sözleşmeye sadık kalmaya çalışın.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Yaptığınız iş için teşekkürler. Lütfen ödemenizi alın - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "Ve şimdi bununla ne yapacağız? İnsanlar kim bilir ne zamandır bunu bekliyordu, sen ise ancak bugün getirdin. Peki, ver bana – belki hâlâ bir işe yarar. Ve umarım artık herhangi bir ödeme almayacağını anlıyorsundur.";
			link.l1 = "Elbette, biliyorum. Al eşyalarını. Hoşça kal.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Yani, gemilere eşlik etmen gerekecek."+pchar.questTemp.WPU.Escort.ShipName1+"' ve '"+pchar.questTemp.WPU.Escort.ShipName2+"'  şehrine "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", için "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))" . Her iki gemi de varış noktasına sağ salim ulaşmalı. Gemileri yerel liman yetkilisine teslim edeceksin. Ücretini de o ödeyecek.";
			link.l1 = "Her şey açık görünüyor. Devam edeyim mi?";
			link.l1.go = "escort_1";
			link.l2 = "Hmm... Ama o tarafa gitmiyorum. Üzgünüm, ama reddetmek zorundayım.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Devam edin. Bu gemiler artık sizin emrinizde.";
			link.l1 = "O halde yelken açıyorum!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hmm... Yanınızda sadece bir gemi görüyorum. Doğru mu?";
				link.l1 = "Evet, "+GetAddress_FormToNPC(NPChar)+" . Bir diğeri ise düşman filosuyla yapılan bir savaşta batırıldı.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Pekâlâ, o zaman. Gemilere eşlik edip yükü teslim etmen gerekiyordu "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Ama görüyorum ki tüm sevkiyatı teslim etmemişsiniz - siz "+FindRussianQtyString(sti(amount))+" kısa.";
					link.l1 = "Bin köpekbalığı aşkına! Kesin o lanet farelerdir! Ama merak etme, "+GetAddress_FormToNPC(NPChar)+", eksik miktarı satın alacağım ve tüm partiyi teslim edeceğim.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... Ama sen "+FindRussianDaysString(iTime)+" geç kaldınız. Bu yüzden işin ödemesinden kesinti yapmak zorundayım. Sözleşmeye göre, geciktiğiniz her gün için toplam tutarın yüzde beşi kadar ceza uygulanır. Şimdi lütfen, ödemenizi alın "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", ve lütfen bundan sonra sözleşmeye sadık kalmaya çalışın.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Pekâlâ, o zaman. Gemilere eşlik edip yükü teslim etmen gerekiyordu "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Yaptığınız iş için teşekkür ederim. Lütfen, ödemenizi alın - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "Yaptığınız iş için teşekkürler. Lütfen, ödemenizi alın - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "Teşekkürler!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Liman’da gemini göremiyorum. Gemini açıkta demirle, sonra tekrar yanıma gel – o zaman konuşuruz.";
			link.l1 = "Pekala, tam olarak öyle yapacağım.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Yani, gemilere eşlik etmen gerekecek "+pchar.questTemp.WPU.Escort.ShipName1+"' ve '"+pchar.questTemp.WPU.Escort.ShipName2+"' şehrine "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", için "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\nAyrıca, yükü geminize yerleştireceğim, "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+" Teslimat için ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Her şey açık görünüyor. Devam edeyim mi?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... Ama ben o tarafa gitmiyorum. Üzgünüm, ama reddetmek zorundayım.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Mükemmel! Filonun komutasını devral.";
			link.l1 = "Öyleyse yelken açıyorum!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "İnanılır gibi değil! Peki, seni neden tuttuk biz? Böyle bir şeye nasıl izin verdin?! Artık ödül söz konusu bile olamaz, umarım bunu anlıyorsun.";
			link.l1 = "Elbette, biliyorum... Neyse, en iyi dileklerimle.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "İnanılır gibi değil! Peki, seni neden tuttuk biz? Böyle bir şeye nasıl izin verdin?! Umarım anlıyorsun, artık refakat için herhangi bir ödül söz konusu olamaz... Üstelik yük de eksik - "+FindRussianQtyString(sti(amount))+"\nGenel olarak, sana sadece kabul edilebilir durumda teslim edilen malların taşımacılığı için ödeme yapacağım, eksik olanların değerini düşerek. "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" ve istediğin yere gidebilirsin.";
					link.l1 = "Hiç yoktan iyidir.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "İnanılmaz! Peki, seni neden tuttuk o zaman? Böyle bir şeye nasıl izin verdin?! Umarım anlıyorsun, artık bu koruma görevi için herhangi bir ödül söz konusu olamaz... Üstelik, büyük bir yük açığın da var.\nEksik malları temin etmeni bekleyecek vaktim yok. Bu yüzden zararın tamamını karşılamak zorundasın - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Yük ise sende kalabilir.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Pekala, fazla heyecanlanma. Al paranı.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Hepiniz delirdiniz mi? Bu düpedüz şantaj! Size hiçbir şey vermeyeceğim!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "İnanılır gibi değil! Peki, seni neden tuttuk biz? Nasıl izin verdin böyle bir şeye?! Umarım anlıyorsun ki, artık koruma için herhangi bir ödül söz konusu olamaz.\nGenel olarak, sadece taşıdığın malların nakliyesi için ödeme yapacağım. Al paranı "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" ve istediğin yere gidebilirsin.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "İnanılır gibi değil! Peki biz seni neden tuttuk? Böyle bir şeye nasıl izin verdin?! Umarım anlıyorsun ki, artık koruma görevi için herhangi bir ödül söz konusu olamaz... Bir gemiyi kaybettin, geldin "+FindRussianDaysString(iTime)+" geç kaldın, üstelik yükün de eksik - "+FindRussianQtyString(sti(amount))+"\nEksik malları temin etmeni bekleyecek vaktim yok. Bu yüzden tüm bedeli karşılamalısın "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Yük ise sende kalabilir.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Pekâlâ, fazla heyecanlanma. Al paranı.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Hepiniz delirdiniz mi? Bu düpedüz şantaj! Size hiçbir şey vermeyeceğim!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "İnanılır gibi değil! Peki, seni neden tuttuk biz? Böyle bir şeye nasıl izin verdin?! Umarım anlıyorsun, artık koruma görevi için herhangi bir ödül söz konusu olamaz... Üstelik, sen geldin "+FindRussianDaysString(iTime)+" geç kaldınız.\nBu yüzden taşıma ücretinden kesinti yapmak zorunda kaldım. Anlaşmaya göre, gecikilen her gün için asıl tutarın yüzde 10'u kadar ceza uygulanıyor. Şimdi, alın paranızı "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", ve gidebilirsin.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Anladım... O halde, bir daha asla hiçbir liman yetkilisinin karşısına çıkmamalısın "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"! Defol!";
			link.l1 = "Sanırım pek bir şey kaçırmadım...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "Bu çok, çok kötü! Seni neden tuttuk, söyleyebilir misin? Gemileri koruman için mi? Yoksa sadece ortalıkta dolaşman için mi?";
			link.l1 = "Anlıyorum. Düşman gerçekten çok güçlüydü ve... ama tartışmanın ne anlamı var ki - olan oldu. Ama yük - yük hâlâ sağlam! O halde gelin, bunu halledelim.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Bakalım, o zaman. Bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iFrahtGoods)+" tutarında "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Ama görüyorum ki tüm sevkiyatı teslim etmemişsiniz - siz "+FindRussianQtyString(sti(amount))+" kısa.";
				link.l1 = "Bin köpekbalığı! Kesin o lanet fareler! Ama merak etme, "+GetAddress_FormToNPC(NPChar)+", eksik miktarı satın alıp tüm partiyi teslim edeceğim.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Bakalım, o zaman. Bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iFrahtGoods)+" tutarında "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+" . Doğru mu?";
			link.l1 = "Kesinlikle doğru, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hmm... Sana emanet edilen gemileri kaybetmekle kalmadın, aynı zamanda geç de kaldın "+FindRussianDaysString(iTime)+". Bu yüzden navlun ödemesini azaltmak zorunda kaldım. Gemileri kurtaramadığınız için navlun ödemesini yarıya indirdim, size sunabileceğim en fazlası bu.\nAyrıca, sözleşmeye göre gecikilen her gün için orijinal tutarın yüzde 10'u kadar ceza uygulanıyor. Şimdi, paranızı alın "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", ve yoluna devam et.";
				link.l1 = "Hiç yoktan iyidir.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Her ne kadar sana emanet edilen gemileri koruyamamış olmandan dolayı son derece üzgün olsam da, en azından malları teslim ettin. Gemileri kurtaramadığın için navlun ödemesini yarıya indirdim, sana verebileceğim en fazlası bu. Şimdi, al ödemenizi - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" ve istediğin yere gidebilirsin.";
			link.l1 = "Hiç yoktan iyidir.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Kasabanın valisine acil bir resmi mesaj iletmeniz gerekecek "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" en geç "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Çok dikkatli ol – düşmanlarımız da o mesajın peşinde olabilir. Teslimat için ödemen – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Kabul ediyorum!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Hayır, sanırım bu sefer pas geçeceğim.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Bu evrakları   dükkan sahibine teslim etmen gerekecek "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" en geç "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+" . Bu, takımadadaki mağazalardaki fiyatların en güncel özeti - değerli bir ticari belge. Dikkatli olunmalı - rakipler peşinize düşebilir. Teslimat için ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Kabul ediyorum!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Hayır, sanırım bu sefer pas geçeceğim.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Bu belge paketini kasabadaki tefeciye teslim etmeniz gerekecek "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" en geç "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+" . Bu, döviz kurları ve hisse senedi fiyatları hakkında çok önemli bilgiler. Çok dikkatli ol – bazı karanlık tipler bu paketin peşine düştü bile. Teslimat için ödemen – "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Kabul ediyorum!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Hayır, sanırım bu sefer pas geçeceğim.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Bu paketi   limandaki ambar sorumlusuna teslim etmelisin "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" en geç "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Yeni için planları içeriyor "+RandPhraseSimple(LinkRandPhrase("brig","corvette","frigate"),LinkRandPhrase("flüt","pinnace","galeon"))+",   benzersiz teknolojik tasarımlar kullanıyorlar. Umarım başka... ilgili tarafların da olduğunu anlıyorsundur, bu yüzden gizlice hareket etmen gerekecek. Teslimat için ödeme - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Kabul ediyorum!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Hayır, sanırım bu sefer pas geçeceğim.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "O halde belgeleri al ve denize açıl. Bol şans... ve Yüce Allah seni korusun.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Gerçekten de yazık... Aslında, bu tür teklifleri genelde kimse kolay kolay geri çevirmez. Ama karar senin, yine de.";
			link.l1 = "Evet, bu benim kararım, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap(false);
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap(false);
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Kahretsin! Demek sonunda seni bulmuşlar. Aslında asker olsaydın, kaptan, belki de her şey farklı olurdu... Nasıl görünüyorlardı?";
			link.l1 = "Yüzlerinde yarım maskeler olan, siyah giysili, güçlü ve iri iki adam; ellerinde baltalar ve çift namlulu tüfeklerle...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Onları bulmaları için hemen valiye haber vereceğim. Peki, görüşürüz. "+GetAddress_Form(NPChar)+" . Yine de, asker olmamanız ne yazık...";
			link.l1 = "Gerçekten üzgünüm, "+GetAddress_FormToNPC(NPChar)+", olanlar için. Neyse, elveda.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Kolonimizde belirli bir malın talebi son zamanlarda büyük ölçüde arttı. Yerel mağazalarda artık stokta yok. Bu yüzden, bana şunu temin etmeni istiyorum: "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+", ve iki katı ödemeye hazırım - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" parça başına. Bu toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, bir de bir ay içinde yetiştirmeye çalışın - malları daha fazla bekleyemem.";
				link.l1 = "Pekala, bu görevi kabul ediyorum.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sizi hayal kırıklığına uğrattığım için üzgünüm, ama şu anda bunu yapamam.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Kolonimizde belirli bir malzemenin talebi son zamanlarda büyük ölçüde arttı. Yerel mağazalarda artık stok kalmadı. Bu nedenle, sizden bana şu malzemeyi temin etmenizi istiyorum: "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+", ve iki katı ödemeye hazırım - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" parça başına. Bu toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, bir de bir ay içinde yetiştirmeye çalışın - malları daha fazla bekleyemem.";
				link.l1 = "Pekala, bu görevi kabul ediyorum.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sizi hayal kırıklığına uğrattığım için üzgünüm, ama şu anda bunu yapamam.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Sömürgemizin cephaneliği ciddi şekilde eksik "+GetGoodsNameAlt(iGoods)+" . Yerel dükkanlarda artık stokta yok. Bu yüzden, bana temin etmeni istiyorum "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+", ve üç katı ödemeye hazırım - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" parça başına. Bu da toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, bir de bir ay içinde yetiştirirsen iyi olur - malları daha fazla bekleyemem.";
				link.l1 = "Pekala, bu görevi kabul ediyorum.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sizi hayal kırıklığına uğrattığım için üzgünüm, ama şu anda bunu yapamam.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Son zamanlarda kolonimizde baş gösteren ateşli hastalık yüzünden tıbbi malzemelerimiz tükendi – depolarda hiçbir şey kalmadı. Vali, kasaba halkının güvenliğinden endişe ediyor. Bu nedenle, bana temin etmeni istiyorum "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+", ve üç katı ödemeye hazırım - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" paket başına. Bu da toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, bir de bir ay içinde teslim etmeye çalış – malları daha fazla bekleyemem.";
				link.l1 = "Pekala, bu görevi kabul ediyorum.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sizi hayal kırıklığına uğrattığım için üzgünüm, ama şu anda bunu yapamam.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Kötü bir hasattan sonra, kolonimiz sürekli olarak ithal gıdaya ihtiyaç duyuyor. Şu anda stoklarımız neredeyse tükenmiş durumda ve mağaza rafları da epey zaman önce tamamen boşaldı. Sizden ricam, bana teslim etmeniz "+GetGoodsNameAlt(iGoods)+" tutarında "+FindRussianQtyString(iGoodsQty)+", ve iki katı ödemeye hazırım - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" paket başına. Bu da toplamda "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Ah, bir de bir ay içinde teslim etmeye çalış - malları daha fazla bekleyemem.";
				link.l1 = "Pekala, bu görevi kabul ediyorum.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sizi hayal kırıklığına uğrattığım için üzgünüm, ama şu anda bunu yapamam.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Harika! Kabul ettiğinize çok sevindim. Umarım yakında tekrar görüşürüz.";
		link.l1 = "Elbette, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Benimle dalga mı geçiyorsun? Sipariş ettiğim kadar mal yok sende!";
			link.l1 = "Üzgünüm, benim hatam...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Pekâlâ, bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iGoods)+" miktarında "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Harika, çok teşekkür ederim. İşte ödemeniz - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Sizinle iş yapmak bir zevkti, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Liman’da gemini göremiyorum. Açıkta demirle, sonra tekrar yanıma gel – o zaman konuşuruz.";
		link.l1 = "Pekala, tam olarak öyle yapacağım.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Bu felaket on gün önce meydana geldi... Kolonimize doğru yola çıkan bir ticaret gemileri kervanı korsanlar tarafından saldırıya uğradı. Aniden çıkan bir fırtına korsanları geri çekilmeye zorladı, fakat ticaret gemileri dağıldı ve birbirlerini gözden kaybettiler. Sonunda, tüm gemiler farklı limanlara ulaştı, bir tanesi hariç. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' ortadan kayboldu ve akıbeti hâlâ bilinmiyor. Muhtemelen ıssız bir adanın yakınlarında bulunabilir "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Sizden oraya gitmenizi, kaybolan gemiye ne olduğunu öğrenmenizi ve eğer hayattaysa onu limanımıza getirmenizi istiyorum. İş bittikten sonra ödemenizi belirleyeceğiz ama emin olun, karşılığını fazlasıyla alacaksınız.";
				link.l1 = "Elbette, kabul ediyorum!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Üzgünüm, ama bu iş bana uygun değil. Korkarım kabul edemeyeceğim.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Bir ticaret kervanı kolonimize varmak üzereydi, fakat limana girmeden hemen önce korsanlar tarafından saldırıya uğradı. Çatışma şu anda devam ediyor. Kale toplarının menzili dışında kaldılar ve elimde eskort gemisi de yok, bu yüzden zavallı tüccarlara yardım edemiyorum. Sen cesur bir kaptansın, bu yüzden müdahale edip tüccarların saldırıyı püskürtmesine yardım etmeni istiyorum! Bunu yapar mısın?";
				link.l1 = "Elbette! Bu bir onur meselesi!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Üzgünüm, ama bu iş bana uygun değil. Sanırım kabul edemeyeceğim.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "Kolonimizin sipariş ettiği silahlar ve cephaneleri taşıyan bir gemi yakın zamanda koloniye ulaştı "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". Onun refakat gemisi bir resife çarptı, ağır hasar aldı ve yakın zamanda limandan ayrılamayacak. Böyle bir yükle ticaret gemisini tek başına göndermeyi göze alamayız.\nOnu kolonimize kadar eşlik etmeyi kabul eder misiniz? Bu iş için ödenecek ücret "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Elbette, kabul ediyorum!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Üzgünüm, ama bu iş bana uygun değil. Ne yazık ki kabul edemeyeceğim.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Gerçekten yazık. Aslında sana güveniyordum...";
		link.l1 = "Ben de üzgünüm. Peki, tekrar görüşene dek, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Harika! Sana güvenebileceğimi biliyordum. Lütfen mümkün olduğunca hızlı ol. Sanırım "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+"  ulaşmak için yeterli olacak "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Al, kimliğini doğrulaman için bu belgeleri götür. Rüzgarın bol olsun, kaptan!";
		link.l1 = "Merak etme, seni hayal kırıklığına uğratmam.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Sonunda! O gemi yeterince uzun süre göz zehirimiz oldu. Komutayı devral o zaman. Geminin adı "+pchar.questTemp.WPU.Escort.ShipName+",   ve kaptanı gelişinizden derhal haberdar edilecek.";
		link.l1 = "Gemiye hazırlanmasını söyle - ilk fırsatta yola çıkacağım.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Liman’da gemini göremiyorum. Şimdilik açıkta bekle, sonra tekrar gel – o zaman konuşuruz.";
		link.l1 = "Tam da bunu yapacağım.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Harika! Bir kez daha güvenilir biri olduğunu kanıtladın. İyi iş çıkardığın için teşekkür ederim. Lütfen, ödülünü kabul et - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". Ve zaman zaman beni ziyaret etmeyi unutma - senin gibi bir kaptan için her zaman bir iki iş bulunur.";
		link.l1 = "Bunu duymak güzel, "+GetAddress_FormToNPC(NPChar)+"! Elbette, işbirliğimiz devam edecek. Saygılarımla!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Liman’da gemini göremiyorum. Şimdilik açıkta bekle, sonra tekrar gel – o zaman konuşuruz.";
		link.l1 = "Pekala, tam olarak öyle yapacağım.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "O halde size güvenli bir yolculuk dilerim. Lütfen aramayı geciktirmeyin! O geminin mürettebatının acil yardıma ihtiyacı olabilir.";
		link.l1 = "Anladım. Bugün denize açılacağım!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Evet, zaten bilgilendirildim. Harika iş çıkardınız, "+GetAddress_Form(NPChar)+"! Bir kez daha güvenebileceğim kişi olduğunu kanıtladın. Al ödülünü - 30.000 peso.\nBeni ara sıra ziyaret etmeyi unutma - senin gibi insanlar çok değerli, ve sana her zaman uygun bir işim olacak.";
		link.l1 = "Bunu duyduğuma sevindim, "+GetAddress_FormToNPC(NPChar)+"! Elbette, işbirliğimiz devam edecek. Her şey gönlünüzce olsun!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Liman’da gemini göremiyorum. Şimdilik açıkta bekle, sonra tekrar gel – o zaman konuşuruz.";
		link.l1 = "Pekala, tam olarak öyle yapacağım.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Evet, bana zaten korsanlarla olan savaşı ve gemisini savunurken ne kadar kahramanca davrandığını anlattı. Harika iş çıkarmışsın, "+GetAddress_Form(NPChar)+"! Bir kez daha güvenebileceğim biri olduğunu kanıtladın. Ödülünü al - 50.000 peso.\nBeni ara sıra ziyaret etmeyi unutma - senin gibi insanlar çok değerli, ve sana her zaman uygun bir iş bulurum.";
		link.l1 = "Bunu duymak güzel, "+GetAddress_FormToNPC(NPChar)+"! Elbette, işbirliğimiz devam edecek. Saygılarımla!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Liman’da gemini göremiyorum. Şimdilik açıkta bekle ve sonra tekrar yanıma gel – o zaman konuşuruz.";
		link.l1 = "Pekala, tam olarak öyle yapacağım.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Ne trajik bir son... Tanrı ruhlarını huzura kavuştursun.";
		link.l1 = "Elimden gelen her şeyi yaptım, "+GetAddress_FormToNPC(NPChar)+". Fırtına durumu daha da kötüleştirdi.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Gerçekten inanıyorum, "+GetAddress_Form(NPChar)+", gemiyi ve o talihsiz denizcileri kurtarmak için elinizden geleni yaptığınızdan şüphem yok. Ama ne yazık ki... Lütfen ödülünüz olan 10.000 peso'yu kabul edin ve hizmetiniz için teşekkür ederim.";
		link.l1 = "Teşekkür edecek bir şey yok, "+GetAddress_FormToNPC(NPChar)+". Gerçekten üzgünüm. Peki, hoşça kal.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Evet, zaten bana kırmızı derili putperestlerle ve ardından bir korsan gemisiyle savaştığını anlattı – tam bir kahraman gibi. Harika iş çıkarmışsın, "+GetAddress_Form(NPChar)+"! Bir kez daha güvenebileceğim biri olduğunu kanıtladın.\nÖdülünü al - 40.000 peso. Ara sıra beni ziyaret etmeyi unutma - senin gibi insanlar çok değerli, ve sana her zaman uygun bir işim olacak.";
		link.l1 = "Bunu duyduğuma sevindim, "+GetAddress_FormToNPC(NPChar)+" ! Elbette, işbirliğimiz devam edecek. En iyi dileklerimle!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Sana güvenebileceğimi biliyordum. Bol şans, Kaptan! Tüm koloni zaferini diliyor!";
		link.l1 = "Beklentilerinizi karşılamaya çalışacağım. Şimdi yelken açıyorum, Tanrı yardımcımız olsun!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Evet, bütün kasaba senin savaşını izliyordu. Zavallı tüccarlar, onlar için gerçekten üzülüyorum. Neyse ki en azından bir gemiyi kurtarmayı başardın, bu yüzden 10.000 peso ödülünü fazlasıyla hak ettin. Lütfen kabul et – ve yardımın için teşekkürler.";
				link.l1 = "Bana teşekkür edecek bir şey yok... O dövüşü kesin bir şekilde kazanamamış olmam talihsizlik, ama elimden gelen her şeyi yaptım. Elveda, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Evet, bütün kasaba senin verdiğin savaşı izliyordu - ve bunu gerçekten ustalıkla yaptın, söylemeliyim. O zavallı tüccara çok üzüldüm... Ama sen olmasaydın, hiçbiri sağ kurtulamazdı, bu yüzden 25.000 peso ödülünü fazlasıyla hak ettin. Lütfen kabul et - ve yardımların için teşekkür ederim.";
				link.l1 = "Öyleyse, eylemlerimle ilgili bu güzel değerlendirme için teşekkür ederim, ama bence bu benim en iyi savaşım değildi - yine de bir gemimi kaybettim. Neyse, kader bu, yapılacak bir şey yok. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Evet, bütün kasaba senin verdiğin savaşı izledi - gerçekten muhteşemdin! O pis korsanların tüm filosunu yok ettin! Artık derslerini aldılar - ama işlerine yaramayacak. Ödülün 50.000 peso - lütfen, kabul et.";
				link.l1 = "Yaptıklarımı bu kadar nazikçe değerlendirdiğiniz için teşekkür ederim! Yardımcı olmak her zaman bir zevk. Ve şimdi, "+GetAddress_FormToNPC(NPChar)+", lütfen müsaadenizle ayrılmak istiyorum.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Hmm, bu kötü. O halde, bundan sonra benim için başka bir iş söz konusu olamaz.";
			link.l1 = "Anlaşıldı. Demek istediğim şuydu...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Yazık kaptan... Yardım etmeye istekli olmamanız gerçekten üzücü.";
			link.l1 = "Bu benim isteğime bağlı bir şey değil, iyi adamım. Anlamalısınız. Hoşça kalın.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Senin derdin ne kaptan?! Hiç mi utanman yok?! Bunu nasıl yapabildin?! Ben işimi bilirim, yıllardır bu görevdeyim. Sigorta sözleşmeleri var, sigorta şirketi de ödemeye hazır, ve sana temin ederim ki sigorta bedeli gayet makul.";
			link.l1 = "Senin derdin ne, bayım? Barut odası patladı, ölümler oldu, şimdi de ihmalkarlığın yüzünden yargılanacaksın?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Hayır! Tabii ki hayır! Tanrım ruhumu korusun, yoksa başımdan olurdum. Ambar tamamen boştu, şükürler olsun Tanrım, şükürler olsun Meryem Ana!\n"+"Ve sorun şu ki, gemi... ya da daha doğrusu, Bay [[[VARx]]]’a aitti. "+sCapitainId+", Karayipler'de iyi bilinir. Üstelik Avrupa'da özel siparişle, olağanüstü özelliklerle inşa edildi. "+"Ve bu gemi sahibi fazlasıyla gururluydu, sağa sola hava atıyordu, tam bir ahmaktı, Allah affetsin... Şimdi ona ne söyleyeceğim ben? En iyisi kendimi öldüreyim, yemin ederim...";
			link.l1 = "Ah, şimdi sorunun ne olduğunu anladım, gerçekten. Peki, bu gemiyi bu kadar özel kılan neydi? Sahibinin onunla bu kadar gurur duymasına sebep olan sıradışı özellikleri nelerdi?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me in the yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "Peki, limanda insanlar ne diyor? Buraya bir tane daha inşa etmek gerçekten imkânsız mı?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Kimse yapamaz. Hatta yakındaki adaya gidip yerlilere sordum. Onlar, Isla Tesoro'da gemi yapımında neredeyse her şeyi başarabilen ünlü bir usta olduğunu söylediler. Ama Isla Tesoro öyle lanet olası uzak ki... Geriye sadece senin gibi özgür kaptanların yardımına güvenmek kaldı. Belki bana böyle bir gemi bulursun. Gerisini ben hallederim\n"+"Sana cömertçe teşekkür edeceğim, sigorta şirketi de aynısını yapacak. Durum alışılmadık, biliyorsun. Kim böyle güçlü bir adamı kızdırmak ister ki?";
			link.l1 = "Evet, bu hiç de kolay olmayacak. Peki, ne kadar vaktim var?";
			link.l1.go = "BurntShip8";
			link.l2 = "Hayır dostum, böyle bir işe karışamam. Kaldı ki, bu özelliklere sahip bir geminin gerçekten var olduğuna dair hiçbir garanti yok. Üzgünüm...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Tanrıya şükür, hâlâ zamanımız var. Mal sahibi Avrupa'ya yelken açtı ve en az yarım yıl dönmeyecek.";
			link.l1 = "Pekâlâ, sanırım hallederim. Sana benzer bir gemi getireceğim. Ama şunu unutma - eğer fazla cimrilik edersen, gözlerinin önünde yakarım onu!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Ne ima ettiğini sanıyorsun, kaptan? Elbette, zamana ihtiyacın olduğunu anlıyorum - bu öyle en yakın su birikintisinden rastgele bir tekne bulmak gibi bir şey değil... Sadece gemiyi bize getir, gerisini bize bırak, sana güvenebilirsin...";
			link.l1 = "Umarım öyle olur... Peki, beni ve iyi haberleri bekle. Hoşça kal.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "Ne hakkında konuşmak istiyordunuz?";
			link.l1 = "Ve eski liman şefi nerede, bay "+NPChar.Quest.BurntShip.LastPortmanName+"? Onunla bir işim var.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Artık buralarda değil. Düşünsene – tanınmış birine ait bir gemiyi yaktı ve sigorta parasını cebe indirdi. Yetkililer bu işi çözmeye çalışırken, istifa edip sessizce Avrupa'ya kaçtı. Gerçekten tam bir dolandırıcı, değil mi?";
			link.l1 = "Evet, o hikayeyi duydum. Üzgünüm, ama gitmem gerekiyor.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "Ne hakkında konuşmak istiyordunuz?";
			link.l1 = "Sana istediğin gibi sıradışı bir gemi getirdim. Şimdi ödülümü bekliyorum.";
			link.l1.go = "BurntShip14";
			link.l2 = "Biliyor musun, "+GetFullName(NPChar)+", hala ihtiyacınıza uygun bir gemi bulamadım. Sanırım bu işi bırakmam gerekecek. Sizi hayal kırıklığına uğrattıysam üzgünüm...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Yazık kaptan... Yardım etmeye istekli olmamanız üzücü.";
			link.l1 = "Bu benim irademle ilgili bir mesele değil, iyi adamım. Lütfen anlayış gösterin. Hoşça kalın.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Gerçekten mi! Peki, yeni gemimizin adı ne?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Affedersiniz, sonra tekrar geleceğim.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Ah kaptan, beni yüzüstü bırakmadığın için çok mutluyum! Ne büyük bir "+GetSexPhrase("iyi bir delikanlı","güzel genç hanımefendi")+" sen olmasaydın, hayatımı kurtaramazdım... Lütfen, paranı birkaç gün sonra almaya gelir misin? Biliyorsun, sigorta işlemlerini halletmem lazım... Bu arada, gemide ufak tefek tamiratlar yapabilirsin - mesela yelkenleri yenile, delikleri kapat, bir de karina temizliği fena olmaz...";
			link.l99 = "Sana, beni kandırmaya kalkarsan gemiye zarar vereceğime dair söz vermiştim. Unuttun mu?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Hayır, hayır, tabii ki hayır! Sözümde duracağım, merak etmeyin. Bakın, yeni gemiyi, tabiri caizse, gizlemek için daha fazla masraf çıkacağını bildiğimden, eski gemi için aldığım sigorta parasını faizle borç verdim. Umarım beni anlarsınız...";
			link.l1 = "Paranın sandığıma ulaştığında her şeyi çok daha iyi anlayacağım. Tekrar görüşene dek.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "Ne hakkında konuşmak istiyordunuz?";
			link.l1 = "Ödülümü almaya geldim. Hâlâ ihtiyacınız olan gemi bende.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Adını bana tekrar hatırlatır mısınız? Hafızam eskisi gibi değil artık – bilirsiniz, bunca telaş arasında...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Affedersiniz, sonra tekrar geleceğim.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Evet, mükemmel. Ödülünü vermeye hazırım, "+FindRussianMoneyString(cn)+". Sigorta şirketi yanan geminin değerini böyle belirledi. Sigorta bedeli kredi sandıklarıyla ödeniyor - nakit yok, üzgünüm.";
			link.l1 = "Ah, bu miktar bana uygun değil. Eminim bu gemi çok daha fazla eder.";
			link.l1.go = "BurntShip21";
			link.l2 = "Evet, doğru. Sana yardımcı olabildiğim için memnunum. Görüşürüz.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "Ne diyorsun kaptan?! Bana güven, ne dediğimi biliyorum. O parayla iki tane böyle gemi alırsın!";
			link.l1 = "Sanırım onu kendime saklayacağım. Bilirsin, ona yeni yeni ısınmaya başladım... Hoşça kal.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "Kaptanlardan biri günlüğünü ofisimde unutmuş. Ne kadar da dalgın! Onu yakalayıp günlüğünü geri vermeni istiyorum.";
				link.l1 = "Ah, bu kolay olacak... Onu alıyorum!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Hayır, onunla ilgilenmem. Aslında bu kendi sorunu.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Oradan bir gemi çalındı. Çalınan gemiyi bulup geri getirmeni istiyorum.";
				link.l1 = "Hmm, peki, soruşturmaya başlamaya hazırım.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Üzgünüm, fakat çalınan gemileri aramakla ilgilenmiyorum.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Harika, işte günlüğü... Gerçekten içimi rahatlattın! Bir gemi günlüğünün kaybolması çok kötü bir şeydir. O kaptanlara hep üzülürdüm...";
			link.l1 = "Eh, bu gerçekten endişelenecek bir durum! Şimdi, o dalgın kaptan hakkında bana daha fazla anlat.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Evet, tabii ki! Adı "+npchar.quest.PortmansJornal.capName+", o   geminin   kaptanı "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" adlı '"+npchar.quest.PortmansJornal.shipName+"'. Kısa süre önce denize açıldı ve  "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "Anladım. Tamam, onu bulacağım. Peki, ödeme ne olacak?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" O sana kendisi ödeme yapacak, bu onun çıkarına. Sen sadece ona bir an önce ulaşmaya odaklan, gerisi hallolur.";
			link.l1 = "Anladım. O zaman, ben gideyim...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Harika! Biliyor musun, çalınan gemi nüfuzlu birine ait, bu yüzden bu iş benim için çok önemli. Bu iş için sana cömertçe ödeme yapacağım...";
			link.l1 = "Anladım. Bana gemi ve çalındığı koşullar hakkında daha fazla bilgi ver.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+"   adında birisi "+npchar.quest.PortmansSeekShip.shipName+"  gece boyunca çalındı "+FindRussianDaysString(rand(5)+10)+" önce. Nöbetçi öldürüldü.";
			link.l1 = "Hmm... Şimdiye kadar çok uzaklaşmış olmalılar. İz artık taze değil, işte sorun da bu.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Doğru, ama yine de hemen alarm vermenin bir anlamı görmedim. Askeri gemi onlara yetişebilirdi, fakat sadece gemiyi paramparça ederdi - ve bu tam olarak istediğim şey değil.";
			link.l1 = "Anladım. O halde aramaya başlayacağım. Umarım şansım yaver gider.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Ne yazık - ama başarıya güvenemezdik zaten.";
			link.l1 = "Evet, gemi çalındığından beri çok zaman geçti.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Yine de, çabalarınız umduğumuz kadar verimli olmasa da, yardımınız için teşekkür ederim.";
			link.l1 = "Elimden gelen her şeyi yaptım...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Harika! Gerçi bunun tam olarak çalınan gemi olduğunu sanmıyorum... Ah, kimin umurunda! Ben bunu alıyorum.";
				link.l1 = "Evet, gerçekten...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Harika! Bana gerçekten çok yardımcı oldun. Ne kadar zor olduğunu hayal bile edemiyorum.";
				link.l1 = "Evet, gerçekten...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Sana ödülünü vermeye hazırım. Şunlardan oluşuyor: "+makeint(sti(npchar.quest.money))+" doblon olarak. Ne yazık ki, bundan fazlasını ödeyemem.";
			link.l1 = "Pekala, bu kadar yeter. Teşekkür ederim ve en iyi dileklerimle.";
			link.l1.go = "exit";
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.money));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Birkaç kayıtlı kaptan var. Özellikle biriyle mi ilgileniyorsunuz?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "Listemde size ilginç olabilecek bir kaptan yok.";
				link.l1 = "Anladım.   Yine de bilgi verdiğiniz için teşekkür ederim.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Pekala, bakalım... A-ha! İşte orada! ","Ah-ha... A-ha! İşte! ","Pekâlâ, o zaman. ")+"Kaptan "+GetFullName(sld)+" "+arCapLocal.date+" yıl önce limanımızdan ayrıldı ve denize açıldı "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Teşekkür ederim. Listeyi tekrar gözden geçirmek istiyorum...";
			link.l1.go = "CapitainList";
			link.l2 = "Pekala, hepsi bu. Başka hiçbir kaptanla ilgilenmiyorum.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Pekala, bakalım... A-ha! İşte orada! ","Ah-ha... A-ha! İşte! ","Pekâlâ, o zaman. ")+"Kaptan "+GetFullName(sld)+" "+arCapLocal.date+" yıl önce limanımızdan ayrıldı ve yelken açtı "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Teşekkür ederim. Listeyi tekrar gözden geçirmek istiyorum...";
			link.l1.go = "CapitainList";
			link.l2 = "Pekala, hepsi bu. Başka hiçbir kaptanla ilgilenmiyorum.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Pekala, bakalım... A-ha! İşte orada! ","Ah-ha... A-ha! İşte! ","Pekâlâ, o zaman. ")+"Kaptan "+GetFullName(sld)+" "+arCapLocal.date+" yıl önce limanımızdan ayrıldı ve denize açıldı "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Teşekkür ederim. Listeyi tekrar gözden geçirmek istiyorum...";
			link.l1.go = "CapitainList";
			link.l2 = "Pekala, hepsi bu. Başka hiçbir kaptanla ilgilenmiyorum.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Pekala, bakalım... A-ha! İşte orada! ","Ah-ha... A-ha! İşte! ","Pekâlâ, o zaman. ")+"Kaptan "+GetFullName(sld)+" "+arCapLocal.date+" yıl önce limanımızdan ayrıldı ve denize açıldı "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Teşekkür ederim. Listeyi tekrar gözden geçirmek istiyorum...";
			link.l1.go = "CapitainList";
			link.l2 = "Pekala, hepsi bu. Başka bir kaptanla ilgilenmiyorum.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Pekala, bakalım... A-ha! İşte orada! ","Ah-ha... A-ha! İşte! ","Pekâlâ, o zaman. ")+"Kaptan "+GetFullName(sld)+" "+arCapLocal.date+" yıl önce limanımızdan ayrıldı ve yelken açtı "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Teşekkür ederim. Listeyi tekrar gözden geçirmek istiyorum...";
			link.l1.go = "CapitainList";
			link.l2 = "Pekâlâ, hepsi bu. Başka bir kaptanla ilgilenmiyorum.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Dinliyorum – hangi gemi, ne kadar süreyle?";
    		Link.l1 = "Lucas Rodenburg beni gönderdi. Gemimi burada ücretsiz olarak demirleyebileceğimi söyledi.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Dinliyorum – hangi gemi, ne kadar süreyle?";
    		Link.l1 = "Richard Fleetwood beni gönderdi. Amiral gemimi burada demirleyebileceğimi ve bunun için 10.000 peso ödemem gerektiğini söyledi.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Evet, doğru. Ama maalesef şu anda geminizi kabul edemem. Rıhtımda yer yok.";
    			Link.l1 = "Ne yazık.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Ve burada bırakmayı düşündüğünüz gemi hangisi?";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "Boşverin, teşekkür ederim.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... Gemilerinizden hiçbirini göremiyorum.";
	    			Link.l1 = "Sadece demirleme imkanını sormak istemiştim.";
	    			Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStock_2":
			// --> andre270925 оставаил тут комментом старый код чтобы забрать куски перевода, если нужно
      //       chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && npchar.id == "Beliz_portman" && !CheckAttribute(npchar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)	// В Белизе скидка 50%
			// {
			// 	NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref)/2;
			// }
			// else
			// {
			// 	if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = MOD_SKILL_ENEMY_RATE/2*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			// 	else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			// }
			// dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', class "+RealShips[sti(chref.Ship.Type)].Class+", rıhtım ücretleri "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" aylık, ödeme bir ay önceden yapılır.";
			// Link.l1 = "Evet, bu bana uyar.";
			// if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			// {
			//     Link.l1.go = "ShipStock_3";
			// }
			// else
			// {
      //           Link.l1.go = "ShipStock_NoMoney";
			// }
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			PortmanCalculatePrices(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', class "+RealShips[sti(chref.Ship.Type)].Class+", rıhtım ücreti "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" aylık, peşin ödenir.";
			dialog.Text = dialog.Text+" Eğer onu bir subay ve mürettebatla bırakırsanız, o zaman onlarla birlikte "+FindRussianMoneyString(sti(NPChar.MoneyForShip)+sti(NPChar.MoneyForCrew));

			Link.l1 = "Evet. Bu benim için uygun.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip)) Link.l1.go = "ShipStock_3";
			else  Link.l2.go = "ShipStock_NoMoney";

			Link.l2 = "Evet. Benim için uygundur. Kaptana ve mürettebata bırakın";
			if (sti(Pchar.Money) >= (sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew))) Link.l2.go = "ShipStock_4";
			else Link.l2.go = "ShipStock_NoMoney";

			Link.l3 = "Hayır, fikrimi değiştirdim.";  
			Link.l3.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Ve bu bana da uyacak, gerekli miktarı topladığında.";
			Link.l1 = "Ah... Sonra tekrar uğrarım.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
		 	LeaveShipInPort(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Pekala. Geminizi ne zaman isterseniz geri alabilirsiniz.";
			Link.l1 = "Teşekkürler.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_4":
		 	LeaveShipInPortWithCrew(NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Pekâlâ. Geminizi ne zaman isterseniz geri alabilirsiniz.";
			Link.l1 = "Teşekkürler.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Hangi gemiyi almayı düşünüyorsun?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and my officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "Hayır, fikrimi değiştirdim.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Başka bir gemi için yeriniz var mı?";
	    			Link.l1 = "Ah, doğru. Teşekkür ederim.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Amiral geminizi limanda göremiyorum. Ve burada yalnızca kendi gemilerinizi geri alabilirsiniz.";
    			Link.l1 = "Pekala, onları sonra almaya gelirim.";
    			Link.l1.go = "exit";
			}
		break;

		case "ShipStockManBack":
			// Лимит офицеров не позволяет забрать  
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "Kaptan, mürettebatınızda başka bir subay için yer yok gibi görünüyor.";  
				link.l1 = "Hmm... O zaman daha sonra geri geleceğim.";  
				link.l1.go = "exit";  
				break;  
			}
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Bakalım... Bu gemi limandan şu saatte ayrılmış: "+chref.quest.Mutiny.date+".";
				link.l1 = " 'Ayrıldı' derken ne demek istiyorsun? O burada, iskelede olmalı!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Gemini almak mı istiyorsun? Rıhtım ücreti için hâlâ borcun var "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "Bir şey mi alıyorsun?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Evet.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Hayır, fikrimi değiştirdim.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			if(CheckAttribute(chref, "DontNullShip"))
			{
				DeleteAttribute(chref, "DontNullShip");
				DeleteAttribute(NPChar, "DontNullShipBeliz");
			}
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "Hangi subayınıza vermemi istersiniz?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring an officer with me for this ship.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I've changed my mind..";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Evet, evet, biliyorum. Ama ücretsiz barınma için sadece bir gemi kabul edebilirim. Lütfen filonuzdaki işleri halledin ve sonra tekrar gelin.";
				link.l1 = "Pekala, sadece amiral gemisini getireceğim.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Evet, evet, biliyorum. Bay Rodenburg'un emriyle, geminizi muhafaza için kabul ediyoruz ve burada kaldığı süre boyunca bir nöbetçi subay tahsis edeceğiz. Lütfen buraya... ve buraya... imza atın.";
				link.l1 = "Pekâlâ... Sanırım artık tüm resmiyetler halledildi, değil mi?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Evet. Artık geminiz için endişelenmenize gerek yok - biz onunla ilgileneceğiz. Siz mynheer Rodenburg'a dönebilirsiniz.";
			link.l1 = "Teşekkür ederim. Hoşça kal.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Evet, evet, biliyorum. Ama ücretsiz demirleme için yalnızca bir gemiyi kabul edebilirim. Lütfen filonuzdaki işleri halledin ve sonra tekrar gelin.";
				link.l1 = "Pekala, sadece amiral gemisini getireceğim.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Evet, tabii ki. Parayı yanında getirdin mi?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Tabii. Buyurun.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Hayır. Birazdan dönerim.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Pekâlâ. Geminizle ilgileneceğiz ve burada kaldığınız süre boyunca bir nöbetçi subay tahsis edeceğiz.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Bir isteğiniz var mıydı, Kaptan?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Subayınız "+GetFullName(chref)+" bilgilendirildi"+NPCharSexPhrase(chref,"","")+" bana    "+NPCharSexPhrase(chref,"o","o")+" Sizin emrinizle denize açılmak zorunda kaldım. İtiraz etmedim "+NPCharSexPhrase(chref,"onu","onu")+".";
			link.l1 = "Kahretsin! Böyle bir emir yoktu! Gemimi o herife emanet etmemeliydim! Eh, neyse, zaten kaybım için yapacak bir şey yok.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Ne sürpriz... Acaba "+NPCharSexPhrase(chref,"o","o")+"Sana nereye gittiklerini söylediler mi, tesadüfen?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Üzgünüm, "+GetAddress_Form(NPChar)+". Adamlarına karşı daha dikkatli olmalısın.";
			link.l1 = "Biliyorum, aptalım. Hoşça kal, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Adadaki eşsiz gemiler ve onlara emanet edilen kişiler gözden kaçmaz. Ancak bu bilgi oldukça değerlidir ve öyle kolayca verilmez.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Anlıyorum. Ciddi niyetimi göstermek için 25.000 peso yeterli olur mu?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "Pekala, belki başka bir zaman.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "Elbette, bu kabul edilebilir. Hangi gemiyle ilgileniyorsunuz?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galyon '"+GetShipName("Kutsal Merhamet")+"'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Kar devriyesi '"+GetShipName("Lady Beth")+"'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "Brig '"+GetShipName("Memento")+"'.";
				link.l3.go = "UniqueShips_Memento";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Amsterdam_InfoPU"))
			{
				link.l4 = "Şirket Amiral Gemisi '"+GetShipName("Amsterdam")+"'.";
				link.l4.go = "UniqueShips_Amsterdam";
			}
			link.l99 = "Bence yeterince biliyorum.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "Holy Mercy, Escorial tarafından Avrupa'dan gönderilerek İspanyol kolonilerini denetlemekle görevlendirildi. Geminin kaptanı Don Alamida, İspanyol tacının ünlü bir hizmetkârı, yolsuzluk ve suçla amansız bir savaşçı ve Katolik inancının tutkulu bir savunucusudur. Holy Mercy, yolculuğuna Havana'da başlayıp yine orada bitirerek koloniler arasında sefer yapar ve yalnızca görevine odaklanır.\nHer limanda Alamida birkaç gün, bazen daha uzun kalır. Bu zamanlarda sokakta bile karşılaşılabileceği söylenir, fakat yerliler böyle bir karşılaşmayı pek istemezler—İspanyollar arasında señor yalnızca korku ve hayranlık uyandırır.\nHoly Mercy'nin tecrübeli ve sadık bir mürettebatı vardır; hepsi bizzat Alamida tarafından seçilmiştir. Her bir denizci, vatanını ve kaptanını hayatı pahasına savunmaya hazırdır. Don Fernando'nun, Holy Mercy'nin asla ele geçirilmemesini emrettiği söylenir ve fısıltılara göre, mürettebat üstün bir kuvvetle karşılaşırsa, geminin ele geçirilmesindense onu derinlere göndermeyi tercih edeceklerdir.";
			link.l1 = "Çok teşekkür ederim.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "Lady Beth gerçek bir güzellik. İngiltere'nin denizcilik dehasının bir harikası, eski Kraliyet Donanması subayı Albert Blackwood'un komutasında. Gerçekten de, herkes böylesine gösterişli bir şekilde firar etmeyi başaramaz! Hizmetten ayrıldı, parlak kariyerini mahvetti ve bir savaş gemisini çaldı—hepsi hazine avı uğruna!\nVe bu boşuna değildi. Şimdiden Barbados'un yarısını satın alacak kadar buldu, ama hâlâ daha fazlasını istiyor. Onu denizde görürsen—yolunu kesmeye kalkışma bile. Gemisi çok iyi, kaptanı ise tecrübeli ve temkinli. Son zamanlarda Blackwood sık sık Cayman'da görülüyor—gece gündüz kazı yapıyor, insanları canından bezdiriyor. Oraya gitmeye karar verirsen—yanına en az altmış adam ve iyi silahlar al... Aslında, bu bile yetmeyebilir\nUmarım iyi nişan alırsın, çünkü eski deniz piyadelerinden oluşan bir birlik de Albay Fox'un komutasında onunla birlikte firar etti. Gerçek profesyoneller, sıradan haydutlara benzemezler. Ve asla Fransız limanlarında ona saldırma—orada koruyucuları ve destekçileri var, bulduklarından pay alıyorlar.";
			link.l1 = "Çok teşekkür ederim.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "'Memento' — gerçek bir korsan efsanesi. Mortimer Grim'in kaptanlığındaki siyah bir brigantin.\n"+"Grim yalnızca köle tüccarlarını hedef alır. Söylenene göre, köleleri özgür bırakır ve idama mahkûm edilenleri altınla kurtarır. Asil bir amaç — eğer gerisini bilmiyorsan.\n"+"Eğer insan taşıması yapmıyorsan, Grim sana dokunmaz. Tuhaf biridir ama prensipleri vardır. Ama ambarında köle varsa... ufukta siyah yelkenler görmemek için dua et.\n"+"'Memento' korsan sığınakları arasında seyreder ama nadiren limana yanaşır. Mürettebat aylarca gemide yaşar, sanki karaya ayak basmaktan korkuyormuş gibi. Rivayete göre, bu gemi bir zamanlar korkunç bir salgından sağ çıkmış — bu yüzden mürettebatı öldürmek neredeyse imkânsızdır.\n"+"Eğer onlara karşı koymayı düşünüyorsan, daha fazla top al yanında. 'Memento'ya çıkmak neredeyse imkânsız — mürettebatı sanki içine cin girmiş gibi savaşıyor, ölümden hiç korkmuyorlarmış gibi. Onları yenmenin tek yolu, gemiyi paramparça edip sığınacak yerlerini ellerinden almak. Kıymıklar onları korkutmaz, ama doğrudan saçma atışı isabet ederse — işte o başka bir mesele.\n"+"İyi şanslar. Ve ölümü unutma.";
			link.l1 = "Çok teşekkür ederim.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Amsterdam":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "4");
			pchar.questTemp.Amsterdam_InfoPU = true;
			dialog.text = "Hollanda Batı Hindistan Şirketi'nin saygın amiral gemisi. Bu gemiyle ilgili her şey gizem perdesine bürünmüş durumda. Komutası, Curaçao'daki deniz sicil dairesinin başı Hendrik van Doorn'da — son derece işini bilen, en zengin ve en etkili kaptanlara paha biçilmez hizmetler sunan bir adam. Onların arasına katılmaya çalışırsan, belki daha fazlasını öğrenirsin.";
			link.l1 = "Çok teşekkür ederim.";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 10) + (sti(pchar.rank)*5); //вознаграждение
	// npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты



void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
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
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}

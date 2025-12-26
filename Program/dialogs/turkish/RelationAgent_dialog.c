int iDiplomatPseudoGlobal;

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;
	
	if (!CheckAttribute(npchar, "PatentPrice"))
    {
        npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;
	
    attrLoc   = Dialog.CurrentNode;
    
    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}
 	
 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}
 	
 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
 	}
 	
 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}
 	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Seni tekrar gördüğüme sevindim.";
			link.l1 = "Yine hizmetinize ihtiyacım var.";
			link.l1.go = "relation";
			link.l2 = "Gitmeliyim.";
			link.l2.go = "exit";

			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))			
			{
				link.l4 = "Sana bir teklif sunmak istiyorum."link.l4.go ="D_ShipLetters_1"; 
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}			

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Kendimi tanıtmama izin ver. Buradaki herhangi bir valiyle senin için konuşabilecek adamım. Tabii ki bu bedava değil, ama bana güven, hizmetlerim verdiğin paraya değer. Yeteneklerim için ödediğine pişman olmayacaksın.";
				link.l1 = "İlginç. Devam et.";
				link.l1.go = "relation";
				link.l2 = "Belki bir dahaki sefere.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}
			
			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "You've found shipping papers." **************		
		case "D_ShipLetters_1":
			dialog.text = "Şartların nedir?";
			s1 = "By a lucky chance, I've found a legit package of the ship documents. Is anyone looking for them?";
			s1 = s1 + "The vessel is still sailing and in the register so don't worry. That stupid owner has just lost it";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Let me see it! Yes, the markers here are actual. You are a lucky "+ GetSexPhrase("man","woman") +"! ";
			s1 = s1 + "I just need a package like this and I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What would you say?";
			dialog.text = s1;
			link.l1 = "Böylesine kraliyet cömertliği! Elbette kabul ediyorum!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Hayır, anlaşma yok.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "relation":
			dialog.text = "Bakalım sana nasıl yardımcı olabilirim.";
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l3 = "İngiltere ile barışmak istiyorum.";
				link.l3.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l1 = "Fransa ile barışmak istiyorum.";
				link.l1.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l2 = "İspanya ile barışmak istiyorum.";
				link.l2.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Hollanda ile barışmak istiyorum.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Kaçakçılarla barış yapmak istiyorum.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Bir kapitulasyon mektubuna ihtiyacım var.";
			Link.l8.go = "patent_0";
			
			Link.l9 = "Ticaret ruhsatın var mı?";
			Link.l9.go = "Licence";
			
			if (isHeroOwnCity(true))
			{
				Link.l10 = "Sömürgelerin sahipliği hakkında bir sorum var.";
				Link.l10.go = "City_Buy";
			}
			
			link.l99 = "Biliyor musun, bunu en iyisi kendim halledeyim.";
			link.l99.go = "exit";
		break;
		
		case "Licence":
			dialog.text = "Her zaman elimde bulunur, farklı dönemlerden. Hangi ülkenin ruhsatını istiyorsun?";
		    link.l1 = "İngiltere'den";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Fransa'dan";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "İspanya'dan";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Hollanda'dan";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Biliyor musun, bunu en iyisi kendim halledeyim.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType":
        	dialog.text = "Dönem?";
		    link.l1 = "30 gün";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 gün";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 gün";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Fikrimi değiştirdim.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
        	dialog.text = "Yani, ticaret ruhsatı"+XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name+"Gen")+" için "+sti(npchar.LicenceType)+" gün, fiyatı "+FindRussianMoneyString(iSumm)+".";
		    link.l1 = "Kabul ediyorum.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Fikrimi değiştirdim.";
			link.l9.go = "exit";
		break;
		
		case "NationLicenceType3":
            iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE*500);
			dialog.text = "İşte burada. Bir limana girerken dost bayrağını çekmeyi unutma. Ve ruhsatın tarihini devriyenin kontrol edebileceğini aklında tut.";
			link.l9 = "Teşekkür ederim.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;
		
        case "No_money":
			dialog.text = "Harika! Yeterli paran olunca geri gel.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "exit";
		break;
		
        case "patent_0":
			dialog.text = "Harika. Öncelikle, ulusa olan sadakatini kanıtlamalısın"+" bunun için mükemmel bir hizmet karşılığında. Herhangi bir valiye git"+//NationNameGenitive(sti(NPChar.nation))+" ve birkaç görevini tamamla. Sonra sana bir lisans verecek.";
			link.l1 = "Söyle bana, "+GetAddress_FormToNPC(NPChar)+", bu sıkıcı formaliteden kurtulmanın bir yolu var mı?";
			link.l1.go = "patent_1";
			link.l2 = "Elveda, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_1":
			dialog.text = "Rüşvet mi istiyorsun!? Lisansı kendim mi hazırlayayım diyorsun?";
			link.l1 = "Kesinlikle!";
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
            {
			    link.l1.go = "patent_2_give";
			}
			else
			{
                link.l1.go = "patent_2_none";
			}
			link.l2 = "Hayır. Elveda, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;
		
		case "patent_2_none":
			dialog.text = "Bunu yapacak o türden bağlantılarım yok. Ve sana tüm mühürler ve imzalarla boş bir ruhsat da bulamam.";
            link.l1 = "Ne yazık. Hoşça kal."+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;
		
		case "patent_2_give":
			dialog.text = "Pekala, bunu senin için ayarlayabilirim. Ne tür bir ruhsat istiyorsun?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "İngiltere'den";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Fransa'dan";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "İspanya'dan";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Hollanda'dan";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Bunu en iyisi kendim halledeyim.";
			link.l9.go = "exit";
		break;
		
		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Bu bir hata. Eğer görürseniz, lütfen ALexusB ile iletişime geçin";
                    link.l1 = "Bana uygun görünüyor. Şartlarını kabul ediyorum!";
                    break;
                case HOLLAND :
                    dialog.text = "Hollanda neredeyse huzurlu bir ülke. Birçok dost edinir, çok az düşman kazanırsın. Ve lisansın kendisi de sana sadece şu kadara mal olacak "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Bana uygun görünüyor. Şartlarını kabul ediyorum!";
                    break;
                case FRANCE :
                    dialog.text = "Fransa'nın dostları ve düşmanları artık senin de dostun ve düşmanın olacak. Düşmanlarına ait gemileri batırmana izin verilecek. Ve bu lisansın kendisi sana şu kadara mal olacak "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Kulağa hoş geliyor! Kime hizmet ettiğim umurumda değil! Fransa da olur.";
                    break;
                case SPAIN :
                    dialog.text = "İspanya'nın çok düşmanı var, bunlar senin de düşmanın olacak! İspanya deniz savaşçılarının ülkesidir. Ve ruhsatın kendisi de sana pahalıya patlayacak "+pchar.PatentPrice+" peso.";
                    link.l1 = "İşte istediğim buydu! Yüksek rütbeli kişiler için dövüşüp görevler yaptığın için şu azıcık parayı al!";
                    break;
                case ENGLAND :
                    dialog.text = "Açıkçası, İngiliz genel valisi cebini bu şekilde dolduruyor. Ve ruhsatın kendisi de sana pahalıya patlayacak "+pchar.PatentPrice+" pesos.";
                    link.l1 = "Pekâlâ. Ona, kaçakçılık ve gemi basarak kazandığım kan paramı ver!";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "Hayır, bu benim için değil.";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Bir anlaşmaya vardığımıza sevindim.";
			link.l1 = "Elveda, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			iDiplomatPseudoGlobal = CalculateRelationContraSum(false);
			dialog.Text = "Pekâlâ. Bunun sana maliyeti olacak "+iDiplomatPseudoGlobal+" pesos.";
			Link.l1 = "Kabul ediyorum.";
			if(makeint(Pchar.money) < iDiplomatPseudoGlobal)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Fikrimi değiştirdim.";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Harika, her şeyi halledeceğim. Seninle çalışacaklar.";
			Link.l99 = "Teşekkürler.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
		break;
        // boal <--
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iDiplomatPseudoGlobal = CalculateRelationSum(i, false);
			dialog.text = "Hm... Ne desem bilemiyorum. Elbette barış isteğini kabul edebilirim "+XI_ConvertString(Nations[i].Name+"Abl")+", bunun bedeli "+FindRussianMoneyString(iDiplomatPseudoGlobal)+".";
			if(sti(pchar.money) >= iDiplomatPseudoGlobal)
			{
				link.l1 = "Sanırım başka seçeneğim yok. Al paralarımı.";
				link.l1.go = "relation3";
			}
			link.l2 = "Hayır, bu çok fazla. Hoşça kal.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Harika! Seninle anlaşmak şaşırtıcı derecede kolay. Merak etme, sorununu 15 gün içinde halledeceğim.";
			link.l1 = "Pekala.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iDiplomatPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
		break;
		
		case "RelationYet":
			dialog.Text = "Senin sorunun şimdi çözülecek. Sadece otur ve bekle, daha hızlı olamaz.";
			Link.l99 = "Teşekkürler.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy":
			dialog.Text = "Hangi koloninin sahipliğini konuşmak istiyorsun?";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "Hayır. Hiçbir şey.";
			Link.l99.go = "exit";
		break;
		
		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Colony "+GetCityName(colonies[i].id)+",   ait olmuştur "+XI_ConvertString(GetNationNameByType(sti(sld.Default.nation))+"Gen")+", yeniden ele geçirme girişimlerini durdurmak için istenen fidye "+FindRussianMoneyString(iSumm)+".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Evet, tam da ihtiyacım olan şey bu.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Hayır, teşekkürler. İlgilenmiyorum.";
			Link.l99.go = "exit";
		break;
		
		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Pekala, anlaşma yürürlükte. Kimseyi yakalamaya çalışmayacağız "+GetCityName(colonies[i].id)+" tekrar.";
			Link.l2 = "Teşekkür ederim. İyi günler.";
			Link.l2.go = "exit";
			Link.l3 = "Bir soru daha.";
			Link.l3.go = "relation";
		break;
	}
}

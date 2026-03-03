// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu üçüncü kez sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben sömürge işleriyle meşgul bir adamım ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Zamanı ve yeri değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama birazdan...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Tutsak hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Merhaba "+NPChar.name+", tutsağınız hakkında konuşmaya geldim.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Tutsak hakkında konuşmak istiyorum.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Tutsaklarla ilgili işlerle uğraştığınızı duydum...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ha-ha. Burada sadece bir tutsağım olduğunu mu sanıyorsun? Adını söyle.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+" . O burada mı?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "O öyleydi. Onu Barbados'tan o çiftlik sahibi Albay Bishop'a sattım – geçen hafta buradayken.";
				link.l1 = "Lanet olsun...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ah, sonunda. Onu Barbados'taki o plantasyon sahibine satmayı düşünüyordum, bir iki haftaya burada olacak... Fidye getirdin mi"+GetSexPhrase("","")+"?";
				link.l1 = "Bak, "+NPChar.name+" , ufak bir sorun var... Aslında o kadar param yok. Ama çalışmaya hazırım.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Onu satmamış olman iyi. İşte paranın - 150.000 peso. Onu nerede bulabilirim?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Çok yavaş kaldınız... Ve neden onunla bu kadar ilgileniyorsunuz? Ben sadece akrabalarıyla pazarlık yapıyordum.";
			link.l1 = "Beni buraya gelmem için çağırdılar.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Pekâlâ, geç kaldınız. Yapabileceğim bir şey yok.";
			link.l1 = "Söylesene, ona kaça sattın, eğer sır değilse?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, değil. Ama sana söylemeyeceğim... Söylersem güleceksin. Ha-ha-ha-ha! Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Pekâlâ, pekâlâ... Bir işim var... Nereden başlayacağımı bile bilmiyorum. Haddini aşmış bir korsanı batırmam gerekiyor.";
				link.l1 = "Ormanda onu öldürmek daha kolay olmaz mı?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Pekala, "+pchar.name+", biliyorsun, işler öyle yürümüyor. Parayı getir, o zavallını alırsın, ha-ha.";
				link.l1 = "Pekâlâ, öyleyse elveda.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "İşler böyle yürümez, biliyorsun... Onun ölmesini istemiyorum, sadece bazılarına ganimetten payımı almamaları gerektiğini öğretmem lazım. Ama sonunda köpekbalıklarına yem olursa, buna da üzülmem.";
			link.l1 = "Neden kendi adamlarınızı onun peşinden göndermiyorsunuz?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hmm... Peki "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" bazı korsanları ganimet paylarının bizim sandığımızda, çok uzakta olmayan bir yerde saklanacağına ikna etti "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". İki gemileri '"+pchar.GenQuest.CaptainComission.ShipName1+"' ve '"+pchar.GenQuest.CaptainComission.ShipName2+"' demir aldı, çok geçmeden yelken açıp gitti "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+". Şimdi neden adamlarıma bu işi emanet edemeyeceğimi anlıyorsun, değil mi?";
			link.l1 = "Anladım. Ne kadar vaktim var?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 to 15 days, no more. It's important to me that they don't get to the stash; it would be nonsense to sink them with valuable cargo. In that case, it would be better if they brought it here...";
			link.l1 = "Pekala, kabul ediyorum. Onları yakalamaya çalışacağım.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Endişelenmeyin. Adamlarım onu geminize götürecek. Peki, siz neden onunla bu kadar ilgileniyorsunuz?";
			link.l1 = "Hayır, istemem. Ailesi onu bana teslim etmemi istedi.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, bu iyi. Adamınız için bu kadar düşük bir fiyat teklif ettiğim için neredeyse üzülüyordum. Ha-ha-ha-ha. Hoşça kalın.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Pekâlâ, "+GetFullName(pchar)+", arkadaşımı sen mi batırdın? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Hayır. Onları yakalayamadım. Ve dönüş yolunda da karşılaşmadım.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "Yaptım. Onları köpekbalıklarına yem olmaları için gönderdim.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Lanet olsun! Her neyse, artık önemi yok! Sıradaki öneriniz nedir?";
			link.l1 = "Belki bana daha kolay bir işiniz vardır?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Dinle, "+NPChar.name+", mahkûmun fiyatını düşür...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Hayır.";
			link.l1 = "Öyleyse hoşça kal...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Fiyatı düşürmek mi?! Senin beceriksizliğin yüzünden malımı kaybettim! Şimdi fiyatı artırmam gerekir! İstersen onu 200.000 pesoya alabilirsin, yoksa defolup gidebilirsin!";
			link.l1 = "Bu çok pahalı... Elveda...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Lanet olsun, peki, al paranı.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Bu zavallıyı alabilirsin...";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ho-ho! Aferin! Al şu zavallıyı ve bol şanslar.";
			link.l1 = "Teşekkür ederim. Hoşça kalın.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "Parayı getirdin mi, Charles? O adamı plantasyona satmak konusunda şaka yapmıyordum";			
			link.l1 = "Dinle, "+NPChar.name+", bir sorun var... O kadar param yok. Ama çalışmaya hazırım.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olmanız iyi. İşte paralarınız – 150.000 peso. Onu nerede bulabilirim?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "Ve neden ne yaptığım umrunuzda? Bence en iyisi siz buradan gidin...";
			link.l1 = "Tshh, sakin ol. Sana bir iş teklifiyle geldim. Esirinle ilgili.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, peki. Kimi fidye karşılığında serbest bırakmamı istiyorsun?";
			link.l1 = "Bekleyin. Buraya kimseyi satın almaya gelmedim, size bir mahkumu satın alma fırsatı sunmaya geldim. Ayrıca, onun için fidye alma şansınız da olacak.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Peki neden benim aracılığıma ihtiyacınız var? Parayı doğrudan kendiniz almak istemiyor musunuz?";
			link.l1 = "Bu benim için oldukça riskli. Yetkililerle başım derde girebilir.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... peki o zaman. Bir bakalım. Esirin kim?";
			link.l1 = "Bu "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Anlıyorum. Yalan söylemiyorsan, bu adil bir alışveriş olurdu. Sanırım bu adam için sana ödeme yapabilirim, "+iTemp+" pesos, ya da bunun yerine size ilginç bir bilgi verebilirim. Seçim sizin.";
			link.l1 = "Parayı alsam iyi olacak. Bu işten artık bıktım...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Devam et, anlat bakalım. Eminim bana ilginç bir şeyin vardır.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Para o zaman. Al onları. Artık bu senin sorunun değil. Satış konusu olan kişiyi buraya getir.";
			link.l1 = "Şu anda kasaba kapılarının yakınında olmalı. Teşekkür ederim! Gerçekten bana çok yardımcı oldunuz.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Rica ederim, bana daha fazlasını getir... Görüşürüz!";
			link.l1 = "İyi şanslar...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: birkaç gün içinde "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" Ana Karadan yüklü değerli mallarla dolu bir İspanyol seferi gelecek. Yükü alacak bir gemiyi bekliyor olacaklar. Eğer bir hafta içinde oraya varırsan, yükü kendin için ele geçirme şansın olacak.\nSenin yerinde olsam, çoktan gemime doğru yola çıkmış olurdum. Ve mahkumu buraya getir.";
					link.l1 = "Teşekkür ederim! Mallar, yaşadığım sıkıntılar için adil bir karşılık olacak. Yolcum da şimdiye kadar şehir kapılarının yakınında olmalı. Size getirilecek.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: yaklaşık bir hafta sonra, bir İspanyol brigantini '"+pchar.GenQuest.Marginpassenger.ShipName1+" değerli mallarla yüklü olarak  yola çıkacak "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Eğer acele ederseniz, onu kolayca yakalarsınız.\nHâlâ buradasınız? Sizin yerinizde olsam, çoktan gemime gidiyor olurdum. Ve mahkûmu buraya getirin.";
					link.l1 = "Teşekkürler! Mallar, yaşadığım sıkıntılara karşılık iyi bir ödeme olacak. Ve yolcum muhtemelen kasaba kapılarının yakınında olmalı. Size getirilecek.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum.";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Bir Hintli tutuklu var. Onu Moskof Fadey yakaladı. Onunla konuşabilir miyim?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Bana söyle, bu Hintliyi gerçekten asacak mısınız? Böyle küçük bir suç için bu kadar ağır bir ceza fazla değil mi?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Yine ben geldim, komutan. Moskof Fadey, Hintliyi serbest bırakmanız için bu dilekçeyi yazdı. Buyurun, burada.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Buraya yerel dükkân sahibinin isteği üzerine geldim, adı "+pchar.questTemp.Shadowtrader.Tradername+".   Bu mektubu size vermemi istedi.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Yine ben geldim. Elimde önemli kanıtlar var, "+pchar.questTemp.Shadowtrader.Tradername+" doğru.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Longway adında bir adamı arıyorum. Duyduğuma göre siz de onu arıyormuşsunuz, Mösyö Subay. Onu bulmakta şansınız oldu mu, ya da belki bir ipucu buldunuz mu?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey hikayesini sana anlattı mı? Onu görmene engel olacak bir sebebim yok, monsieur. O Kızılderiliyi görmeye gelen ilk kişi sen değilsin. On gün sonra her vatandaş ona bakabilecek, çünkü onu güneşte sallandıracağız...";
			link.l1 = "Yani, hapishaneye girebilir miyim?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Sana zaten söyledim, 'Bunu yapmanı yasaklamak için bir sebebim yok.' Devam et.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Burada yenisiniz, değil mi, monsieur? Avrupa'dan yeni geldiniz herhalde? Sömürgelerdeki durumu anlamıyorsunuz. Bu idam, Fransız kolonistlerin mülküne göz diken o Kızılderili piçlerine ders olacak. Ayrıca, Fadey'in kendisi de bunu özellikle istiyor ve burada hem çok saygı gören biri hem de valimizin yakın dostudur.";
			link.l1 = "Cezayı hafifletmenin bir yolu var mı? Hâlâ bunun çok ağır olduğunu düşünüyorum...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ah, bırak şimdi felsefeyi! Eğer bu Hintlinin kaderi gerçekten umurundaysa, git Fadey’e sor. Fadey onun serbest bırakılması için dilekçe yazarsa, biz de kabul ederiz.";
			link.l1 = "Anlaşıldı, subayım. Fadey'e gideceğim.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(okuyarak) Hm... Bu Fadey tuhaf biri... Önce halka açık bir idam istedi, şimdi de bu Kızılderili'nin serbest bırakılmasını talep ediyor... Her neyse, sanırım valinin tüm dostları onun gibi. Peki, gidebilirsin ve bu Kızılderili'yi alabilirsin.";
			link.l1 = "Teşekkür ederim, subayım!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Yine mi o "+pchar.questTemp.Shadowtrader.Tradername+"   şikayetleriyle! Peki, bakalım bu sefer neymiş... (okur)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Yine saçma tahminler ve tek bir sağlam kanıt yok! Peki. Ona söyle, muhafızları uyarıp kasabayı aratmam için bu kesinlikle yeterli değil.";
			link.l1 = "Ona bunu söylememi mi istiyorsun?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Aynen öyle – ve tercihen, kelimesi kelimesine. Ne demek istediğimi anlayacaktır. Bu sinir bozucu kişiye cevap yazmak için kağıt israf etmeyeceğim.";
			link.l1 = "Anladım. O halde hoşça kal.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "Ve topladığınızı iddia ettiğiniz bu 'önemli' kanıt nedir?";
			link.l1 = "Kaçakçılarla, malları gayriresmî dükkânlarından satın almak için bir anlaşma yaptım. Ajanları bu gece liman idaresi ofisine gelip beni sözde 'dükkanlarına' götürecek.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hmm... Güzel, harika iş çıkardınız, kaptan! Şimdi devam ediyoruz. Adamımızı toplantılarına göndereceğiz, saklandıkları yeri bulup hepsini tutuklayacağız. Girişiminiz için teşekkür ederim!";
			link.l1 = "Yardımcı olmaktan her zaman memnuniyet duyarım. Operasyonunuzun başarılı olacağından eminim.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Kim? Uzun... Yol mu? Son zamanlarda kasabamızda hiç İngiliz görmedim.";
			link.l1 = "Hayır, Longway... Çinli.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Pekala, pekala. Peki, bu Longway denen adamı neden arıyorsunuz, monsieur?";
			link.l1 = "O benim arkadaşım. Olanları zaten duydum - bu üzücü bir yanlış anlaşılma, sizi temin ederim.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Onu arıyorum çünkü Takımadalar'da tanınmış bir suçlu.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, bir yanlış anlaşılma olmuş. Onu oracıkta yola getirmeye çalışmıyorduk, en azından öyle bir niyetimiz yoktu. Sadece onunla konuşmak istedik... en başta. Fakat şu saldırgan sarı adamınız sadece birkaç şehir muhafızını öldürmekle kalmadı, peşine düşen birlikleri de ormanda katletti.";
			link.l1 = "Başka bir birlik göndermeyi düşünüyor musunuz? Adamlarınızla birlikte gidebilir, onunla konuşup sakinleştirebilir ve yeni bir felaketi önleyebilirim. Katliamlar durursa ve Longway şehri tamamen terk ederse bu yeterli olur mu?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Normal şartlar altında, sana katılabilirdim. Ama bak, öldürülenlerden biri bir subaydı – gelecek vaat eden genç bir teğmen, Majestelerinin gözdesi. Şehir yas tutuyor. Buna göz yummak ya da telafi etmek mümkün değil. Anlıyor musun?";
			link.l1 = "Tam olarak anlıyorum. Arkadaşımın davranışları için özür dilerim. Sizi daha fazla rahatsız etmeyeceğim.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Bilirsin, Tanrı bilir ormanda neler olup bittiğini. O adamları kim olsa öldürebilirdi.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "Ve bir subayın komutasındaki tüm devriye ekibini kim alt edebilmiş olabilir, sence?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Güvenilir) Haydutlar, başka kim olabilir? İtiraf etmekten utanıyorum ama yakın zamanda büyük bir çeteden zor kurtuldum.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Ama bunu nasıl bilebilirim? Herkes yapmış olabilir—haydutlar, korsanlar, casuslar...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, şaşırmam, senin cüsseni düşününce, Kaptan. Evet, bugünlerde adada böyle alçaklar eksik olmuyor...";
			link.l1 = "Kesinlikle! Yani, devriyeyi ve zavallı genç teğmeni katletmiş olabilirlerdi.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Ne yazık ki, bu tamamen mümkün.";
			link.l1 = "Kesinlikle. Bu yüzden bir kez daha rica ediyorum, bir sonraki arama ekibine katılmama izin verin – Longway beni dinler, böylece daha fazla ölümün önüne geçebiliriz.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Pekâlâ. Ama hâlâ bir 'ama' daha var, efendim.";
			link.l1 = "Ve o da ne?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Ormanda olanların aksine, arkadaşınızın şehirdeki suçu açıkça kanıtlanmış durumda. Bu cezasız kalmayacak. Yani, eğer onun şehirden sağ çıkmasını istiyorsanız, bu ölümlerin bedeli ödenmeli.";
			link.l1 = "Pekâlâ. Bunun bana maliyeti ne olacak, Mösyö Subay?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Üç yüz dublon. Bu para şehre gidecek, pazar meydanındaki kavgacılara değil.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Elbette. Üç yüz dublon - buyurun.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Bu sefer kasabaya doblonlarımı getirmedim. Ama onları almama izin verirseniz...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Mükemmel. Sorumluluğunu kanıtladın. Sıradaki ekibin bilgilendirmesini tamamlamak üzereyiz. Katılmana izin veriyorum.";
			link.l1 = "Teşekkür ederim. Hoşça kalın, Mösyö Subay.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Dün doğmadım ben. Kaçmaya niyetin olduğunu biliyorum – altınlar için değil, o sevgili Çinlin için.";
			link.l1 = "Sana söz veriyorum, Longway ile şehirden ayrılmayacağım.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Sözler, sözler... Laflarından bıktım, Kaptan. Bu lanet sarı tenli adamı kendi ellerimizle yakalamadan hiçbir yere gitmiyorsun.";
			link.l1 = "Eğer Longway'i hemen oracıkta öldürmeyeceğine söz verirseniz, emrinize uyacağım, Bay Memur.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Ama bugün şehrin yasalarını bizzat ben mi çiğnedim?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "O zaman bilmiyorsun. Ben şimdiki sezgime güveneceğim – Çinli her halükarda yakalanmalı.";
			link.l1 = "Şu anki sezgin mi? Ama Longway’in ormandaki herkesi öldürdüğüne dair hiçbir kanıtın yok.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "Ve onun masumiyetine dair bir kanıtın var mı? Yok mu? O zaman şu sarı derili adamını aziz gibi göstermeyi bırak. Beni anladın mı?";
			link.l1 = "Tam olarak anladım. Arkadaşımın davranışları için özür dilerim. Sizi daha fazla rahatsız etmeyeceğim.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Korkarım henüz gitmenize izin veremem, Kaptan.";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Demek istediğim şu ki, bu Longway senin arkadaşın olduğuna göre, onun peşinden gidip birlikte kaçmaya çalışmayacağının hiçbir garantisi yok. Bu yüzden, bu sarı derili celladı biz yakalayana kadar seni burada tutmak zorundayım.";
			link.l1 = "Emrinize uyacağım, ama Longway'i hemen oracıkta öldürmeyeceğinize söz verirseniz, Bay Memur.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Ama bugün şehir yasalarını şahsen ben mi çiğnedim?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Hiçbir şey için söz veremem. Kim bilir arkadaşınızın aklında ne var, ya da bizi görünce yeni bir katliam başlatır mı. Bu arada, lüks konaklamanızın tadını çıkarın, Kaptan.";
			link.l1 = "Çok komik...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Anla, sana karşı kişisel bir husumetim yok. Ve haklısın – hiçbir suç işlemedin. Ama sarı tenli arkadaşının adaletten kaçmamasını sağlamamız gerekiyor.";
			link.l1 = "O halde, böyle sahte bir şekilde alıkonulmaya asla izin vermeyeceğimi anlayın.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "Bu durumda, sizi susturmak zorunda kalacağız, efendim.";
			}
			else
			{
				dialog.text = "Yeter artık! Çavuş, takımı o lanet mağaraya götür ve Çinliyi bul! Bununla bizzat ben ilgileneceğim...";
			}
			link.l1 = "Hayatta izin vermem.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Bir ödül avcısı, öyle mi? Normalde senin gibilerle uğraşmayı sevmem, ama bu sefer çıkarlarımızın örtüşmesi işime geliyor. Görünüşe göre bu sarı tenli olan, namlı bir katilmiş. Hem kasabada hem de ormanda birçok adamımı öldürdü.";
			link.l1 = "Onu bir süredir Takımadalar boyunca kovalıyorum.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Lanet olası alçak! Şöyle yapacağız: Ben başka bir tim toplayacağım, sen de onlarla gideceksin. Bu sefer kaçacak yeri yok, senin yardımınla başarılı olma şansımız daha yüksek. Ama benden ödül bekleme – sen bir kelle avcısısın, ödemen seni tutanlardan gelecek. Benimle iş birliği yapmana izin verdiğim için bile minnettar olmalısın.";
			link.l1 = "Doğru söylüyorsun. Sonra görüşürüz, subay. Adamlarından biri Çinli dostumuzla bir karşılaşmadan daha sağ çıkarsa, sana nasıl geçtiğini bildiririm.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Haklısınız. Siz ikiniz tanışıyor musunuz? Birbirinize kim olduğunuzu sorabilir miyim?";
			link.l1 = "O, gemimde seyir subayı ve...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Onu arıyorum çünkü Takımadalar'da tanınmış bir suçlu.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Haritalardan çok silahlarla daha iyidir. O Çinli uşağınızın ne yaptığından haberiniz var mı?";
			link.l1 = "Doğrusunu söylemek gerekirse, hayır, çünkü henüz yeni yanaştım ve aramaya başladım. Eminim ki bu sadece bir yanlış anlaşılmaydı.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Kesinlikle. Ona bu kadar düşkünsen, sen onun nesisin? Fark etmez – önemli olan şehre geliş amacın.";
			link.l1 = "Yasadışı bir şey yok, efendim. Ama “artık önemi yok” derken neyi kastettiniz? Yoksa o...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Evet. Mezarlığın biraz uzağındaki tepelerden birinin arkasına gömüldü. Kutsal babalar, bir putpereste uygun bir Hristiyan cenazesi yapılmasına izin vermediler.";
			link.l1 = "Nasıl oldu, eğer bir sır değilse?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Çok basit - şehre geldi, durmadan etrafta dolanıp araştırıyordu. Onunla konuşmaya, burada ne yaptığını öğrenmeye çalıştık, ama birkaç adamı öldürdü ve ormana kaçtı. Peşine defalarca arama ekibi gönderdim, hepsini tek tek yok etti! Onu bir mağarada tuzağa düşürmek zorunda kaldık, nişancılar da işin geri kalanını halletti.";
			link.l1 = "Ve ne aradığını bilmiyor musun? Bak, daha önce hiç böyle bir şey yapmamıştı – eskiden gemimde rotacıydı. Ama sonra benden çalıp kaçtı.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Aklımdan tamamen çıkmış, evet. Demek onun yaptıklarından sen de zarar gördün? Bu sana ders olur, Kaptan. Bir daha güvenemeyeceğin biriyle uğraşmamayı öğrenirsin. Sarı tenli adamlara asla güvenme – sözümü unutma!";
			link.l1 = "Tamam, bunu aklımda tutarım. Onun hakkında bir şey bulabildin mi?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Çalınan malları geri almak mı istiyorsun? Cebinde biraz gümüş vardı, yani senden bir şey çaldıysa, çoktan harcamıştır. Bir de başka bazı kağıtlar vardı... geminin seyir defterinden mi? Zaten hiçbir şey anlamadık - belki de bir tür şifreydi? Her şey kana bulanmıştı, sağlam kalan kısmı bile okuyamadık.";
			link.l1 = "Şey, evet. Teşekkür ederim. Günlüklerimi ve not defterlerimi bir başkasının eline geçerse ne olur diye hep endişelenmişimdir...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "Bunun için koca bir şifre sistemi uydurmak zorunda kalmak mı? Zamanına ve emeğine acımadın mı hiç? Al bakalım. Gümüşe gelince - kızma ama onu şehre geri verdik. O Çinli o gün birçok adamımı toprağa gömdü.";
			link.l1 = "O halde ısrar etmeyeceğim. Hoşça kal.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

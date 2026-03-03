void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Rahatsız ettiğim için özür dilerim, Senyor Kaptan, ama bu gerçekten çok önemli.";
			link.l1 = "Umarım öyledir, Alonso. Eğer her biriniz burayı kendi yeriniz gibi basıp içeri dalmaya başlarsa, başımız belaya girer. Peki, ne oluyor?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Sandığınızın karıştırıldığını fark ettik.";
			link.l1 = "Ne?! Bir dakika... Bunu nasıl anladın? Ve hepiniz benim kamarada ne yapıyordunuz?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Siz dışarıdayken - ister şehirde olun ister ranzalarda dinlenin - kamaralarınızı ara sıra temizliyoruz. Hiç fark etmediniz mi? Yoksa sadece unuttunuz mu?";
			link.l1 = "Ah, doğru ya. Artık gidebilirsin.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Kaptan Charles, bakın! Birisi büyük çekmecenizi karıştırmış.";
			link.l1 = "Ne? Bunu ne zaman fark ettin? Kimin yaptığını biliyor musun?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Yakın zamanda, seni görmeye gelirken. Ruhlar kimin olabileceği konusunda sessiz.";
			link.l1 = "Güzel bir dokunuş olmuş, Tichingitu. Şimdi müsaadenle, bir şey eksik mi diye bakmam lazım.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hey, Kaptan, neye bakıyorsun? Birisi eşyalarını karıştırmış. Ben bile fark ettim.";
			link.l1 = "Sen değil miydin? Sonuçta, sana François kadar cömert ödeme yapmıyorum.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, eğer hırsız ben olsaydım, size söyler miydim? Değerli eşyaları alır, arkamı toplar giderdim. Bu dağınıklık bana göre değil.";
			link.l1 = "Bunu itiraf etmekten nefret ediyorum ama haklısın. Neyse Claude, iğnelemelerini sonra sakla. Şimdi hırsızın ne çaldığına bakmam gerek.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Kaptan, bugün birinin dolabınızı karıştırdığını fark ettim. Siz fark etmediniz mi?";
			link.l1 = "Ne? Folke, ben sürekli sandığı kontrol etmiyorum, hem her zaman kamarada da değilim. Doğruyu söyle - sen miydin? Yine bir halt mı karıştırdın, karaya çıktığımızda bir sürü banka kredisi mi çektin?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Hiçbir şekilde, Kaptan. Cebimde ya da sandığımda size ait hiçbir şey yok. Ve asla da olmayacak.";
			link.l1 = "Umarım öyle değildir. Gidebilirsin - neyin eksik olduğuna bakacağım.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_0");
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, değil mi?";
			link.l1 = "Yüzünüzden anladığım kadarıyla cevabı zaten biliyorsunuz. O halde, ne istiyorsunuz?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Senin kafan.";
			link.l1 = "Büyüleyici! Şunu söylemeliyim ki, bu konuşmanın başlangıcını beğendim. Ama daha ileri gitmeden önce, en azından kimi incittiğimi söyleyebilir misiniz? Belki bir anlaşmaya varabiliriz.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Biz acemi değiliz, Monsieur de Maure. Size söylesek bile bir faydası olmazdı – işverenimiz zaten Takımadaları terk etti. Onlara zarar veremez ya da özür dileyemezsiniz. Paramızı aldık, şimdi de anlaşmanın bizim kısmını yerine getirme zamanı.";
			link.l1 = "Eğer zaten ödemenizi aldıysanız, neden daha fazla kan dökesiniz?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Biz acemi değiliz. İtibarımıza değer veririz.";
			link.l1 = "Korkarım bu sefer bunun üstesinden gelemeyeceksiniz.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Bunu göreceğiz. İşimiz bitince cesedini arayın! Ne bulursanız yakın!";
			link.l1 = "Ne yakayım?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Maskeli adamın söylediği şey... Acaba...?";
			link.l1 = "Ne oldu, Longway? Peşime ödül avcıları ilk kez düşmüyor, ama bu sefer alışılmadık derecede endişeli görünüyorsun.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway, bu adamları senin peşine kimin gönderdiğini bildiğini düşünüyor, Efendim Kaptanım.";
			link.l1 = "Bilmem gereken bir şey var mı?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Bu Lord Rodenburg'un yöntemi - ona yardım eden ama fazla şey bilenleri ortadan kaldırmak.";
			link.l1 = "Gerçekten mi... O maskeli adam, patronunun yakın zamanda Takımadaları terk ettiğini söylemişti. Bu tam da Lucas'ın planladığı şeydi! Sence daha fazla saldırı beklemeli miyiz?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Her şeye hazırlıklı olmak akıllıca olur, Efendim Kaptanım.";
			link.l1 = "Akıllıca sözler. Öyle olacağız. Ama Lucas neyin peşindeydi? Bende ne olduğunu sanıyordu? Bir fikrin var mı, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, hayır, Longway bunun ne olabileceği hakkında hiçbir fikre sahip değil.";
			link.l1 = "Bu üzücü. Ama tamam, hadi buradan gidelim.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			ReturnOfficer_Longway();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Efendim Kaptanım, Longway sizinle konuşmak istiyor. Çok önemli bir mesele.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Ne oldu, Longway? Lucas'ın vedalaşma şekli mi seni endişelendiriyor, yoksa yeni bir şey mi keşfettin?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Tabii! Ne düşünüyorsun?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Ne yazık ki, hayır.";
			link.l1 = "O halde nedir, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway söyleyemez. Ama... izin isteyip ayrılmak istiyor.";
			link.l1 = "Ayrılmak mı? Yani, tamamen mi? Neden, Longway? Kaptanın olarak, sebebini bilmeye hakkım var.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "Doğru, Efendim Kaptanım. Ama Longway ne bir işçi ne de bir hizmetkâr. Kendi isteğiyle yardıma geldi, aynı şekilde de gidebilir. Sonsuza dek olmayacak – halletmesi gereken önemli bir mesele var. İş bitince Longway geri dönmeyi umuyor.";
			link.l1 = "Bu mesele nedir? Anlat bana - eğer kaptanın olarak değilse bile, seninle çok şey yaşamış biri olarak.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Longway'in söyleyebileceği tek şey, uzun zaman önce bir yemin etmiş olması. Şimdi onu yerine getirme zamanı geldi. Yoksa... Longway'in hayatının bir anlamı kalmaz.";
			link.l1 = "Haklısın Longway - sen bir mahkum değilsin, ben de bir gardiyan değilim. Gitmekte özgürsün. Yolun açık olsun.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Gidebilirsin, ama en azından nereye gittiğini söyle. Çok soru sormadan yardımcı olabilirim.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Benim de önemli bir görevim var – kardeşimi kurtarmak. Bunun için her adama, sana da, Longway, ihtiyacım var. Sensiz başaramayız.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Beni acıma duyguma ya da görev bilincime oynamaya kalkma. Çok iyi anlıyorum. Hiç yemin ettin mi, Efendim Kaptanım?";
			link.l1 = "Elbette biliyorum. Şimdi her şeyi olduğu gibi anlat, ben ve adamlarım sana mutlaka yardım edeceğiz.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway yapamaz. Sadece... yapamaz. Bu büyük bir sır, üstelik paylaşmak bana bile düşmez.";
			link.l1 = "Bu çok kötü. Aramızda güven olduğunu sanmıştım. Gemiden ayrılmıyorsun - artık tüm subaylar benim tarafımda.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Haklısın Longway - sen bir mahkum değilsin, ben de bir gardiyan değilim. Gitmekte özgürsün. Yolun açık olsun.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Bunu yapamazsın!";
			link.l1 = "Maalesef, yapabilirim Longway. Şimdi görevine geri dön.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Beni bu kadar kolay bırakacağınızı düşünmemiştim. Teşekkür ederim, Efendim Kaptanım.";
			link.l1 = "Ah, önemli değil. Ama söyle bana - işin bitince seni nerede bulabilirim?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway ne kadar istese de gerçekten söyleyemiyor. Ama Efendim Kaptanım’ın yardım etme isteğini takdir ediyor.";
			link.l1 = "O halde öyle olsun. Yeminini yerine getirdiğinde seni nerede bulmamı istersin?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "İşimi bir ay içinde bitirmeyi umuyorum. Ondan sonra, Longway seni Basse-Terre'deki meyhanede bir hafta daha bekleyecek.";
			link.l1 = "Pekala, ne dersen de, dostum. Bu bir veda değil. Basse-Terre'de görüşürüz.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Pekâlâ, merhaba, Kaptan.";
			link.l1 = "Sırıtışınızı beğenmiyorum, efendim.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Yıkıldım. Sana sonunda özgür olduğunu söylemeye geldim. Ama bu lüks kamarada daha fazla kalmak istersen, elbette kalabilirsin.";
			link.l1 = "Hiç de değil. Yani, Longway bulundu mu? Nerede o? Hücrelerden birinde mi?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "Başka bir dünyada, daha çok ona benzer bir yerde - hiçbirimizle konuşmaz, doğrudan savaşa girerdi.";
			link.l1 = "Kahretsin! Onu yakalayabilirdin.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Bazı insanları öldürmek, yakalamaktan çok daha kolaydır, biliyorsun değil mi? Sana karşı bir şey beslemediğimize sevinmelisin – o Çinlin yüzünden yine bir katliam yaşandı, onunla başa çıkmak için birkaç keskin nişancı daha getirmek zorunda kaldık.";
			link.l1 = "Evet, gerçekten öyle. Bunun için teşekkür ederim.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Bu arada, madem dostunuzdu, üzerinde bazı kağıtlar bulduk. Ne olduklarını anlamadık - siz daha iyi bilirsiniz herhalde. Kanla kaplanmamış yerlerinde bir takım saçma şeyler yazıyordu.";
			link.l1 = "Bu... Kahretsin. Onları geri getirdiğiniz için teşekkür ederim. Hoşça kalın, subay.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Bizimle gelin, Komutan sizinle konuşmak istiyor.";
			link.l1 = "Bunun Çinli'yi arayışımla ilgili olduğunu varsayıyorum?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Kendiniz göreceksiniz, monsieur.";
			link.l1 = "Bir suçla mı itham ediliyorum?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Hiç de öyle değil. Kimse sizi tutuklamaya ya da alıkoymaya çalışmıyor. Şimdilik. Komutan sizinle konuşmak istiyor dediğimde, tam olarak bunu kastettim.";
			link.l1 = "Ah, peki...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Bir fikrin var mı? Bu sarı tenli adam ölümcül derecede tehlikeli. Buraya gönderilen ilk ekip biz değiliz. Emirler emirdir, ama sağlam bir plan olmadan içeri dalıp aptalca ölmek istemiyorum.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "O orada tamamen yalnız, ben ise seninleyim. Onunla ben ilgileneceğim - siz bana koruma sağlayın. Hallederiz.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Bir tane var. Hepiniz burada öleceksiniz.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Endişelenme, sadece onunla konuşacağız.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Üzgünüm, ama bugün hepiniz öleceksiniz. Ve bunu yapan bir Çinli olmayacak.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Yani sen bir kelle avcısı değilsin... Ama olsan bile, o lanet Çinli'nin dostusun!";
				link.l1 = "Doğru. Zaten senden kurtulmam gerekecekti – kaçınılmaz olanı ertelemenin anlamı yok.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Ne demek istiyorsun?! Yardım edeceğine söz vermiştin!";
				link.l1 = "Bence bize zaten huzurlu bir çıkış yolu vermezdin. Kişisel bir şey değil.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Buna inanmak isterim.";
				link.l1 = "Daha beterleriyle karşılaştım. Bir Çinli adam bizi bitiremez. Hadi, çocuklar!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Ya konuşma planladığımız gibi gitmezse?";
				link.l1 = "Bundan nefret ederim, ama o zaman kendimi savunmam gerekecek. Hadi gidelim.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Efendim Kaptanım?! Longway inanamıyor, onlarla birlikte olduğunuza!";
			link.l1 = "Hayır, Longway, sadece konuşmaya geldim! Sandığın gibi değil!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "O zaman yalnız gelirdin. Bu askerlerin yardımıyla bana saldırmak için gardımı düşürmeye çalışıyorsun!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Edebilseydim, yapardım. Sana henüz saldırmamalarının tek nedeni benim. Sakin ol, konuşalım, olur mu?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Saçmalamayı bırak! İsteseydim seni çoktan öldürürdüm. Silahlarını bırak, konuşacağız. Bu kaptanının emri.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Evet. Longway size güveniyor, Efendim Kaptanım.";
			link.l1 = "İşte, şimdi daha iyi. Şimdi, bana söyle...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, neler oluyor? Bu da ne... dokunaklı bir buluşma mı? Hani bize o Çinli vahşiyi ortadan kaldırmamızda yardım edecektiniz, değil mi?";
				link.l1 = "Benim. Onu yanıma alıyorum, ve bu öldürmeler sona erecek. Komutana onu birlikte öldürdüğümüzü söyleyeceksin. Anlaştık mı?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Aferin, Kaptan! Silahlarını bıraktı. Aramızda olman güzel. Şimdi onu komutana götürelim.";
				link.l1 = "Neden böyle bir şey yapayım? Longway'in yaptıkları için altınla yüklü bir ceza ödedim - hem de cömertçe. Diğer subaylarınız buna şahitti - doğrulayacaklardır. Komutan, adamımı gemiye götürmeme izin verdi.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Komutan bu kanlı altından bıkmış olabilir, ama ben değilim. O kanlı mağarada öldürdüğü adamlardan bazıları benim dostumdu. Ayrıca, Çinliyi öldürsek de umurunda olacağını sanmıyorum.";
			link.l1 = "Emin misin öğrenmek istediğine? Ve öldürülen arkadaşların hakkında... o küstah haydut çetesini duydun mu hiç? Herhalde onlardı.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, onların iddia ettiği kadar çok askeri öldürmedin, değil mi?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Evet, Efendim Kaptanım. Longway o çeteyi gördü. Onlar mağaranın derinlerine saklandılar, Longway’i fark etmesinler diye. Ve Longway, haydutlarla askerler arasında konuşmaların, küfürlerin ve kavganın seslerini duydu.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Gördünüz mü? Her şey yerine oturuyor. Longway'in öfkesi olabilir, ama o dürüst bir adamdır. Gidiyoruz. Bize dokunursanız üniformanızı lekelersiniz. Hoşça kalın, baylar.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Olmaz, monsieur! Adam bizim bir sürü adamımızı öldürdü, şimdi de elini kolunu sallayarak kurtulacak mı diyorsun?! Ya şu herifi öldürmemize yardım edersin, ya da en azından yolumuzdan çekilirsin!";
			link.l1 = "Korkarım müdahale etmem gerekecek. Gerçekten üzgünüm.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Eğer sadece konuşmak isteseydiniz, silahımı bırakmamı istemezdiniz. Ama bir kaplan, pençelerini çekse bile yine de kaplandır. Longway’e ihanet etmeye çoktan karar verdiğiniz belli—yalan söylemenize gerek yok. Kendinizi savunun, Kaptan!";
			link.l1 = "Siktir!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Onunla başa çıktığımıza inanamıyorum! Ama söyle bana, neden sana Kaptan dedi?";
				link.l1 = "Göründüğünden daha karmaşık, dostum. Komutanınızı ikna etmem gerekiyordu. Önemli olan sonuç, değil mi? Sonuçta Longway öldü ve ben de sana bu konuda yardımcı oldum.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Senin varlığın bile işe yaramadı - yine de üstümüze atladı. Lanet olası vahşi...";
				link.l1 = "Onun hakkında böyle konuşmamalısın. Bize saldırdı çünkü üzgündü ve seninle birlikte olduğumu sandı.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Belki. O halde, hoşça kalın, monsieur. Çinli adamın sonunda öldüğünü komutana kendimiz söyleyeceğiz.";
				link.l1 = "Çok iyi, teşekkür ederim. Hoşça kalın, çocuklar.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Üzgün olsun ya da vahşi olsun, fark etmez - daha önce birçoğumuzu öldürdü, ilk kanı o döktü.";
				link.l1 = "Onu o hale getiren bir şey olmalı. Ama üzerinde durmayalım. Ben gidiyorum, sen de uygun gördüğünde komutana dönebilirsin. Hoşça kal.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Efendim Kaptanım?";
			link.l1 = "Seni her yerde aradım, Longway. Şehirde epey bir karmaşa çıkardın. Konuşacak çok şeyimiz var, hemen gemiye dönelim.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Orada!";
			link.l1 = "Misafirimiz var anlaşılan. Biraz gecikeceğiz gibi görünüyor.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Daha fazlası geliyor!";
			link.l1 = "İnatçı herifler - bunu kabul ediyorum. Burada çok açıkta kaldık. Mağaraya gidelim - kendimizi savunmamız daha kolay olur.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Burada sonsuza kadar kalamayız.";
			link.l1 = "Ve tüm bu olanlardan sonra söylemek istediğin ilk şey bu mu, Longway? Sence de artık neler olduğunu açıklamanın zamanı gelmedi mi?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Efendim Kaptanım, Longway...";
			link.l1 = "Ama haklısın - burada kalamayız. Hadi, başka bir devriye gelmeden gidelim. Yelken açınca gemide konuşuruz.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "Beyaz adamın kurnazlığı ve kötülüğü sınır tanımaz.";
			link.l1 = "Hey, ben de beyazım! Ayrıca, onların arkadaşlarını ve silah arkadaşlarını öldürdün - kızgın olmaya hakları var.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Onları affediyor musunuz, Efendim Kaptanım?";
			link.l1 = "Seni affediyorum, Longway. Ve sana insanları tenlerinin rengine göre yargılamamanı tavsiye ediyorum. Bunu en iyi sen anlamalısın. Lafımız yarım kaldı - nerede kalmıştık...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Kaptan! Arkanda!";
			link.l1 = "Ah, bugün bize doğru düzgün konuşma fırsatı vermeyecekler...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Anlaşıldı, Efendim Kaptanım.";
			link.l1 = "Bu iyi, ama burada oyalanmayalım. Seninle konuşacak çok şeyimiz var. Beni takip et - gemiye dönüyoruz.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
		
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Efendim Kaptanım, gerçekten siz misiniz...?";
			link.l1 = "Evet, Longway. İyi misin?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway iyi. Teşekkür ederim. Ama, Kaptanım! Bakın!";
			link.l1 = "Mağaraya koş, çabuk! Orası savunma için iyi bir yer!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway askerlerin hâlâ gelip gelmediğini kontrol edecek.";
			link.l1 = "Birlikte gideceğiz - tüm garnizona karşı savunmamızı tutamayız.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Evet, Efendim Kaptanım?";
			link.l1 = "Konuşacak çok şeyimiz var. Şimdi beni takip et - hemen demir almamız gerekiyor.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Tekrar yardım ettiğiniz için teşekkür ederim, Efendim Kaptanım. Eminim aklınızda birçok soru vardır.";
			link.l1 = "Az bile söyledin. Neden o askerleri öldürdün? Zevk için öldürmediğini biliyorum-bunu biliyorum.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Hayır, Longway yapmaz. Askerler Longway’i durdurmaya çalıştı, hapis bir seçenek değildi. Dinlemezlerdi; Çinliye değil, sadece beyaz adama o inceliği gösterirler.";
			link.l1 = "Diğer beyazların sözünü de her zaman dinlemiyorlar, ama ne demek istediğini anladım. Yine de, şehirde onları sığır gibi katletmek mi? Basse-Terre'de ne yapıyordun?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "Bundan sonra birlikte çalışalım. İnsanlar genelde muhafızları çağırmak yerine benimle konuşur... genellikle. Ama cidden, bana görevinizi anlatın. Size yardımcı olayım.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Lütfen, Efendim Kaptanım, Longway'i anlayın. Bunu tek başına yapacağına yemin etti. Üzerine gitmeyin. Longway'e en azından bunu borçlusunuz.";
			link.l1 = "Gerçekten minnettarım, ama o zamanlar van Merden'le kendim başa çıkabilirdim. Yine de, en başından beri ödeşmiştik—sen yüzümü kurtardığımı söyledin, sen de hayatımı kurtardın. Şimdi ise seni bir kez daha kurtardım.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... doğru söylüyorsunuz, Efendim Kaptanım. Longway, beyaz adamlar arasında gerçek dostunun siz olduğuna inanıyor. Bir zamanlar böyle düşünmüştü, ama acı bir şekilde yanılmıştı. John Murdock'u hatırlıyor musunuz? Johan van Merden'i?";
			link.l1 = "Ne garip, van Merden'den bahsetmeniz. Son zamanlarda, birisi arşivinden birkaç sayfayı gözümün önünde koparıp aldı. Sizin davanızla bir ilgisi var mıydı? Hırsızı bulabildiniz mi?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Yaptım. Hırsız... Longway'di. Çok üzgün, Efendim Kaptanım. O zamanlar size tamamen güvenip güvenemeyeceğini bilmiyordu.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Arkadaşlıktan bahsediyorsun ama arkamdan beni soyuyorsun? Bu ilk ve son kez, Longway. Anladın mı?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				Notification_Reputation(false, 61, "low");
			}
			else
			{
				link.l1 = "Peki bunu nasıl başardın, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				Notification_Reputation(true, 61, "low");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway anladı. Ciddiyetle söylüyor.";
			link.l1 = "Umarım öyledir. Şimdi bana anlat, bu hayata nasıl geldin - kime, ne zaman ve ne söz verdin.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Evet, Efendim Kaptanım\nLongway, hayatta kalan kendisi için en önemli kişiyi arıyor-Chang Xing.";
			link.l1 = "Chang Xing-en yakın arkadaşın mı?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Senin nezaketin sayesinde, mürettebatın geri kalanı bana çabucak alıştı ve bana güvenmeye başladı.";
			link.l1 = "Pekâlâ, anladım. Övgüye pek açık değilsin ama iyi iş çıkardın Longway... tabii eğer gelişinle ortalığı dağıttıysan, toparladıysan.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Doğru. Ama bunun için zaman yok.";
			link.l1 = "Sanmıyorum. Ama bunu bir daha yapmamaya çalış, olur mu? Bir şeye ihtiyacın olursa, sadece sor. Bana güvenebilirsin. Şimdi, bana yemininden bahset.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Elbette, Longway yükünü sizinle paylaşmaktan memnun, Efendim Kaptanım.\nLongway, kendisi için hayatta kalan en önemli kişiyi arıyor - Chang Xing.";
			link.l1 = "Chang Xing-en iyi arkadaşın mı?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing benim ailem, kız kardeşim. Yıllar önce kayboldu. Onu bulmak için Longway, nerede olduğunu bilebilecek olanları arıyor.";
			link.l1 = "Bu van Merden'in arşiviyle ne ilgisi var? Kız kardeşinizin kaybolmasıyla bağlantılı mı?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Evet, doğru. Her şey birbirine bağlı. Longway ve Johan yıllar önce, sizin Formosa dediğiniz topraklarda, ben Takımadalar'a gelmeden çok önce tanıştılar.";
			link.l1 = "Birbirinizi bu kadar uzun zamandır mı tanıyorsunuz? Ve van Merden de işin içinde miydi? Ne hikaye ama! Onun kız kardeşinizin kayboluşuyla ne ilgisi vardı?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Bana çok kötü insanları aramamda yardım etti—beyaz adamların standartlarına göre bile. Oliveiro Fermentelos, Antoon van Diemen ve Joep van der Vink.";
			link.l1 = "İsimlerine bakılırsa, biri Portekizli, diğer ikisi ise Hollandalı.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Evet, doğru. Ama arayış sonuçsuz kaldı. Longway sabırla Cennetin yol göstermesini bekledi. Bu yüzden van Merden’in arşivini ele geçirdiğinde, onu incelemeye karar verdim. Oliveiro’dan bahseden ilk sayfaları bulunca, onları koparıp kamaradan kaçtım.";
			link.l1 = "Her şey sonunda hikayenin bir parçası oluyor.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Ama hikayenin kendisi daha yeni başlıyor. Efendim Kaptanım, Longway'in arayışını en başından öğrenmek ister misiniz? Oturup dinlemeye hazır mısınız?";
			link.l1 = "Tam da bu yüzden sizi kamaraya çağırdım. Devam edin.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Buraya Çinliler alınmaz. Burası saygın insanlar için saygın bir mekân—sizin gibiler için değil.";
			link.l1 = "Sadece bir sorum var. Sormama izin verin, sonra gideceğim.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Önce düzgün konuşmayı öğren! Sana söyledim-senin gibiler burada istenmiyor.";
			link.l1 = "Oliveiro Fermentelos'u nerede bulabilirim? Söyleyin, yoluma devam edeyim.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Sen de sağır mısın? Sabır taşımı çatlatma, yoksa bu oda yakında sarı bağırsak kokacak.";
			link.l1 = "Benim halkım burada binlerce yıldır yaşıyor. Burası bizim adamız, ama basit bir meyhaneye bile giremiyor muyuz?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Vay, büyük laflar ediyorsun ha? Bunun için asılabilirsin. Defol!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Büyük derdini duydum, küçük dostum. Bu kadar yüksek sesle konuşmamalıydın–yanlış isim, yanlış yer.";
			link.l1 = "Bu adam hakkında bir şey biliyor musun?! Söyle bana!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Sakin ol, dostum.";
			link.l1 = "Özür dilerim.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Özürünü istemem, ama paranı isterim. Belki o zaman sana yardım ederim. Ben Marcelo Schulte. Ya sen? Paran var, değil mi?";
			link.l1 = "Benim adım Chang Tu. Param var. Bu yeterli mi?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(ıslık çalar) Escudo, peso, gulden, doblon... ve hatta sizlerin o tuhaf paralarından bile var. Bu işimi görür. Tamam, Chung Chung, adam hakkında ne bulabileceğime bakacağım. Merak etme, neredeyse her gün buradayım, paran güvende. Her gün uğra, mutlaka karşılaşırız.";
			link.l1 = "Umarım. Hiç param kalmadı...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang! Sen zaten buradasın.";
			link.l1 = "Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Fark etmez, dostum.";
			link.l1 = "Oliveiro'nun nerede olduğunu öğrendin mi?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Hayır, en ufak bir fikrim yok.";
			link.l1 = "Param!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Bu kadar tedirgin olma! Hiçbir şey öğrenmemiş olsaydım, tekrar yanına gelmeye cesaret edebilir miydim? Seni, gerçekten bilen biriyle tanıştıracağım. Şanslısın, Asyalıları çok sever. Hatta hizmetçileri bile var—hem de hizmetçi kızlar. Sizin o pis dilinizi de öğreniyor. Adı Johan van Merden. Seni, konutun yakınındaki iki katlı bir evde bekliyor olacak.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Sen Chang Chang'sın, öyle mi? Gir içeri, çekinme.";
			link.l1 = "Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Öyle mi? Özür dilerim. O Marcelo ve onun şaka geçidi... Ne yazık ki çok az kişi kültürünüzle ilgileniyor. Ve hepsi sadece farklı bir dil konuştuğunuz ve gözlerinizin şekli yüzünden. Ama siz zekisiniz. Siyahlar gibi değilsiniz, hehehe.";
			link.l1 = "(Mandarin) Demek ki kaçakçı yalan söylememiş—gerçekten kültürlü bir adamsınız. Ve gerçekten bizim dilimizi konuşuyorsunuz?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Kültürüm hakkında sıcak sözleriniz için teşekkür ederim. Siz Johan van Merden olmalısınız?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Ah... Sadece birkaç kelime anlayabildim. Hâlâ öğreniyorum, biliyorsunuz. Devam edebilir misiniz, Hollandaca?";
			link.l1 = "Nasıl isterseniz. Siz Johan van Merden misiniz?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Evet, Chung Tu, benim. Oliveiro Fermentelos'u aradığını duydum. Nerede olduğunu biliyorum, ama önce bana söyle-neden onu arıyorsun? Vereceğin cevap, benimkini belirleyecek.";
			link.l1 = "O... son kalan ve en değerli aile üyemi - kız kardeşim Chang Xing'i kaçırdı.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "O zaman sizi hayal kırıklığına uğratmalıyım, Chang Tu. Artık onun için muhtemelen hiçbir umut yok. Büyük ihtimalle zengin bir plantaj sahibine ya da bir geneleve köle olarak satılmıştır. Her halükarda, onu kurtaramazsınız.";
			link.l1 = "Chang Xing'in hâlâ hayatta olduğuna inanıyorum. Oliveiro ona göz koydu. O ise gururla reddetti. Ben evde yokken onu kaçırdı. Ve... ailemizi öldürdü.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Ben... çok üzgünüm. Eğer durum buysa, Chang Xing, değil mi?-hala hayatta olabilir. Şöyle yapalım: bana biraz zaman ver, Oliveiro'nun şu anda tam olarak nerede olduğunu öğreneyim. Bir hafta diyelim. O zaman tekrar görüşürüz. Şehir kapılarının dışında buluşalım-buradaki gözlerin seni izlediğini kim bilebilir. Alışık olduğumdan fazla bulaşmak istemem, umarım anlarsın.";
			link.l1 = "Ben... Ben size derinden minnettarım, Mynheer van Merden. Bir sonraki buluşmamızı dört gözle bekliyorum.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Merhaba, Chung Tu. Gözlerindeki ateşi görüyorum. Haberim var, ama iyi değil.";
			link.l1 = "Her türlü haber benim için son derece önemli. Lütfen, anlatın bana, Bay van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Evet... Fermentelos yaklaşık bir ay önce Batavia'ya gitti. Elimdeki tek bilgi bu. İyi haber şu ki, orada bir süre kalmayı planlıyor, yani şimdi giderseniz yakalarsınız. Kötü haber mi? Genel Vali Anthony van Diemen'in yakın dostu. Ona yaklaşamazsınız.";
			link.l1 = "Bu haber yeterli. Size minnettarım, Bay van Merden. Hemen yola çıkacağım.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Bir şey bana bunu söyleyeceğini hissettirdi, bu yüzden senin ve Chang Xing'in şansını eşitlemek için yardım etmeye karar verdim. Eski bir dostum olan Oliver Trust'a bir mektup yazdım. Batavia'da bir dükkânı var. Bana bir iyilik borçlu, bu yüzden sana yardımcı olacaktır.";
			link.l1 = "Ben... Ne diyeceğimi bilmiyorum...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Basit bir “teşekkür ederim” yeterli. Eğer şehirde Oliveiro’yu bulamazsan, Morning Star’ı ara. Onu her zaman gemisi üzerinden bulabilirsin. İyi şanslar, dostum—senin ve kız kardeşinin buna ihtiyacı olacak.";
			link.l1 = "Tüm kalbimle teşekkür ederim, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Sen kimsin, burada ne yapıyorsun? Sizin gibilerle ticaret yapmam.";
			link.l1 = "Sana bir mektup getirdim.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ah, haberci! Oysa bugün mektup beklemiyordum. Burada kal! Bir bakayım.";
			link.l1 = "Sen Oliver Trust mısın? Van Merden beni sana gönderdi.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Okuma yazmam var, biliyorsun. Normalde seni gönderirdim, ama van Merden gibiler hayır cevabını kabul etmez. Sonunda, van Diemen'le hesaplaşmanın vakti geldi.";
			link.l1 = "Hedefim Fermentelos.   Peki ya van Diemen?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Bu seni ilgilendirmez. Sana yardım ettiğim için minnettar olmalısın. Şimdi dikkatlice dinle, yoksa bunun kötü bir fikir olduğuna karar verebilirim. Fermentelos'u tanıyorum. Bir süredir buradaydı ama artık burada değil. Morning Star birkaç hafta önce ayrıldı. Tanrı bilir ne zaman geri döner. Yani hedefin değişti ve artık Fermentelos'un bir dostu...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Evet. Bunu da biliyor musun? Johan mı anlattı sana? Ah, van Merden... cesur bir herifsin. Ama madem van Diemen'i de biliyorsun, onun yüksek mevkiini de biliyorsundur, değil mi? Genel Valinin yanına nasıl ulaşmayı planlıyorsun? Onun konağını basarak değil herhalde!";
			link.l1 = "Chang Tu usta bir savaşçıdır.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Usta bir savaşçı, öyle mi? Farkındasın, artık birbirimize dolandık, değil mi? Ya seni yakalarlarsa bana ne olacak? Senin güvenliğin ve kendi güvenliğim için sana yardım etmek zorundayım. Van Diemen, konağında yaşamasının dışında, şehrin dışındaki plantasyona ve metresi Vette'ye de düzenli olarak gidiyor.";
			link.l1 = "Bana yardım edeceğinden bahsetmiştin.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Her insanın bir tutkusu, bir hobisi olmalı bence. Benimki ise nadir ve değerli silahlar toplamak. Bazen geçmişleri olur, bazen olmaz, ama her zaman ölümcüldürler. Koleksiyonum senin seferin için faydalı olabilir. Şimdi söyle bakalım, van Diemen’e pusu kurmayı nerede düşünüyorsun?";
			link.l1 = "(Konut) Madem bu kadar iyi silahınız var, en iyi kılıcı alacağım. Onunla, Chang Tu beyaz adamlar arasında rakipsiz olacak.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantasyon) Onları plantasyon yolunda pusuya düşüreceğim - kaçacak yerleri olmayacak.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Hanımefendi) Hanımefendi - orada pek kimse olmaz, bu yüzden muhafızlar zamanında tepki veremez.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Güzel seçim! Etkilendim. Bundan en iyi şekilde yararlanmak için iyi bir ateşli silaha ihtiyacın olacak. Söyle bakalım, Chang Tu, ne kadar uzağa nişan alabilirsin?";
			link.l1 = "Doğrusunu söylemek gerekirse... çok uzağa değil, ıskalamamalıyım."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Uzaklardan saldıracağım - düşmanım ona nereden vurduğumu bile anlamayacak.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification(GetConvertStr("Sniper", "AbilityDescribe.txt")+" Unlocked", "Longway");
			SetCharacterPerk(pchar, "Sniper");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Anladım. O halde, bunu alın! Antika bir Portekiz kuleli tüfeği, büyük kalibreli fişek atıyor. Artık bunlardan yapmıyorlar, Eski Dünya'da bile.";
			link.l1 = "Çocukken birini görmüştüm...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Yani, bunu nasıl kullanacağını biliyor musun?";
			link.l1 = "Hayır...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Unutmayın, değiştirilebilir mekanizma zamanla paslandı. Yağlamak işe yaramaz - artık tamamen bozuldu. Kurmak zor, bu yüzden şimdi yapalım. Dikkatlice izleyin - biraz kuvvet uygulayın, şöyle. Ama çok bastırmayın, yoksa kırarsınız.";
			link.l1 = "Böyle mi?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Aynen öyle.";
			link.l1 = "Anlaşıldı. Çok teşekkür ederim!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "bullet", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "bullet");
			
			dialog.text = "Gerçek bir avcı tüfeği! Dikkatli ol, bu bir hediyeydi. Hem süslü hem ölümcül olan nadir silahlardan biri bu. Çift namlulu bir av tüfeği! Taşırken ağır, kullanması kolay. Onunla nasıl ateş edeceğini çözdün mü bakalım?";
			link.l1 = "Anlaşıldı. Çok teşekkür ederim!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = " Muhafızlar konusunda haklısınız, ama tehlikeyi küçümsemeyin. Van Diemen şehirde hiçbir yere sağ kolu Joep van der Vink olmadan gitmez. ";
			link.l1 = "Yani, şimdi Vette ile birlikteler mi...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Ne? Ha! Hayal gücün gerçekten kuvvetliymiş, Çinli! Antoon tam bir korkak, van der Vink de orada, birileri onların 'özel zamanını' bozarsa diye onu korumak için bekliyor.\nJoep her zaman kalın bir siper zırhı giyer – çoğu soğuk silaha karşı geçilmezdir. Bu yüzden senin de özel bir şeye ihtiyacın olacak. Al şu rapiri. Uzun, çoğu kılıçtan daha sağlam ve iyi bir kılıç gibi hafif.";
			link.l1 = "Zırhlı düşmanlarla savaşmak için bir rapier...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Zırhın kendisini hedef alma - bu bir estok değil. Aralıklara ve savunmasız noktalara vur, kasık, koltuk altı ve boğaz gibi. Onu yıprat, oyunu sen kur. Joep aynı zamanda ağır bir balta kullanıyor, bu yüzden darbelerini karşılamaya çalışma - onun yerine kaçın\nAçık bulamazsan diye, şu çakmaklı tüfeği al. Genelde saçmayla doldurulur, ama senin için çelik oklar hazırladım.";
			link.l1 = "Tüfek için oklar...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Garip, değil mi? Eskiyle yeninin karışımı. Tek elle ateşlenmek için tasarlandı, ama ağır gelirse iki elini kullan. Çoğu öyle yapıyor\nVe bak, şu hasır zırhı dene. Joep’in göğüslüğünden daha hafif ama yine de iyi korur. Baltası doğrudan isabet ederse sakın izin verme – öyle bir silaha Milan zırhı bile dayanmazdı. Anladın mı?";
			link.l1 = "Evet, anladım. Teşekkür ederim, Bay Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Kendine fazla mı güveniyorsun? Belki de sana koleksiyonumdan bahsetmek için acele ettim. Ama... artık işin içine girdin. Gündüz vakti bir konağa saldırmak cesurca bir hareket, kimsenin beklemeyeceği bir şey. Bu kılıç işini görecektir. Dünyanın en iyisi değil belki, ama saplamak, kesmek ve parçalamak için birebir.";
			link.l1 = "Clewang! Bu bıçağı tanıyorum. Komşu adalardaki insanlar sık sık böyle birini kullanır.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification(GetConvertStr("TannedLeather", "AbilityDescribe.txt") +" Unlocked", "Longway");
			SetCharacterPerk(pchar, "TannedLeather");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Teşekkür ederim, Bay Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Bekleyin, işimiz bitmedi. Hayatta kalmanız ikimizin de yararına. Şunu alın, savaş sonrası yaralarınızı iyileştirir. \nBir de bu iksiri alın. Tadı ve kokusu berbat, ama vücudunuzdaki her türlü zehri öldürür. Joep van der Vink, Van Diemen’in koruması, silahlarını o pislikle sıvar. Kendini beğenmiş herif, böylece üstünlük sizde olur.";
			link.l1 = "Sana ne kadar teşekkür etsem yetmez, Efendim Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "En iyi teşekkürün, yakalanırsan beni ele vermemek olurdu. Gerçi büyük ihtimalle seni oracıkta öldürürler. Ama eğer hayatta kalırsan, Van Diemen’a ölümünü bana borçlu olduğunu söyle. Bunu yapabilir misin?";
			link.l1 = "Hiç sorun değil. Tekrar teşekkür ederim, Bay Trust. Hoşça kalın!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Dur! Nereye gidiyorsun, Çinli?";
			link.l1 = "Malikaneye.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Bu bir kinaye sorusuydu, dahisin. Oraya senin gibi birini kim alır sanıyorsun?";
			link.l1 = "Mynheer Van Diemen ile işim var. Lütfen geçmeme izin verin.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Vali generalin adını biliyor musun? Peki... bana işinin ne olduğunu söyle. İletirim ve sana cevapla dönerim.";
			link.l1 = "Benim konuşmam sadece Mynheer Van Diemen ile. O beni bekliyor. Kenara çekil, yoksa pişman olursun.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Pekala, pekala, fazla sevinme, dar gözlü. Ya benim dediğim olur ya da hiç olmaz.";
			link.l1 = "O zaman kendi yolumdan gideceğim.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Lanet olası köylü! Seni kim tuttu? Sana onlardan daha fazla öderim!";
			link.l1 = "Siz beyazlar sadece altını önemsiyorsunuz. Ejderhalar soyunuza lanet etsin. Bilgi almaya geldim, ama insanınız beni içeri almıyor.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Ne istiyorsun?!";
			link.l1 = "Fermentelos. Şimdi nerede?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro mu? Ama neden onu istiyorsun ki? Sana hiçbir şey söylemeyeceğim!";
			link.l1 = "Ailemi öldürdü ve kız kardeşimi kaçırdı. Size tavsiyem, konuşmaya başlamanız. Kendi iyiliğiniz için.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Bana ne yapacaksın? Bütün garnizon yakında burada olacak.";
			link.l1 = "Lynchy'i duydunuz mu? Bu, benim kültürümde bir ceza. 'Bin Kesikle Ölüm' anlamına gelir.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Bana bu kadar çok yara açacak vaktin olmayacak, seni aptal!";
			link.l1 = "Bu bir deyim. Cellat, yaraları teker teker açar. Ya da vücuttan parçalar keser. Konuşmaya başlamazsan, vaktimiz yettiği kadarını yaparız.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Dur! Dur, pis herif. Söyleyeceğim, her şeyi anlatacağım. Yeter ki dur. Joep! Sonunda! Bunca zamandır neredeydin lan?!";
			link.l1 = "Ne kötü bir zamanlama...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Hemen bir doktora görünmen lazım. Buradaki işim biter bitmez seni götürmene yardım edeceğim. Sen! Ne halt ediyorsun orada, sarı kasap?!";
			link.l1 = "Sarı Kasap mı? Hoşuma gitmedi desem yalan olur. Ama bana sadece bir soru lazım, kimse de cevap vermeye yanaşmıyor...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Hangi soru?!";
			link.l1 = "Oliveiro Fermentelos nerede? Sadece bunu söyleyemez misin?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Fermentelos'u umursamıyorum! Parayı ve bilgiyi sana kim verdi?!";
			link.l1 = "Oliver Trust. Bu arada, bana sana ölümünü borçlu olduğunu söylememi istedi.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Güven mi?! Ha-ha-ha-ha-ha-ha-ha! O pinti, sırf plantasyonunu aldık diye intikam alabileceğini sanıyor? Seninle işim bittiğinde, dükkânını da, canını da alacağız.";
			link.l1 = "Vaktimi boşa harcıyorsun.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(Mandarin dilinde) O zaman, iyi bir pusu yeri arayalım.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(Mandarin) Bu paslı şeyle, yaklaşmam gerekecek. Hızlı bir atış - keskin ve acımasız. Korku ve panik gerisini halleder.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(Mandarince) Tam burada. İlk başta beni fark etmeyecekler bile. En iyi savaşlar hiç başlamayanlar... ya da çabucak, az kanla bitenlerdir.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Pis yaratık... Kaçak köle misin sen? Böyle bir silahı nasıl edindin? Yoksa biri mi tuttu seni...?";
				link.l1 = "Vakit yok! Bana hemen Oliveiro Fermentelos'un nerede olduğunu söyle!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, komik... Zaman yok - kan karnımdan akıyor. Cehennemde yan, kafir...";
			link.l1 = "(Mandarin dilinde) Hayır!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(Mandarin dilinde) Neden, neden, neden?! Şimdi Fermentelos'u nasıl bulacağım?!";
			link.l1 = "Ama önce saklanmam gerek - birisi bu kan gölünü çoktan ihbar etmiş olmalı...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hik! Bir Çinli! Buraya senin gibi birinin davet edileceğini beklemiyordum. İzlemeyi mi seviyorsun, ha? Hehe.";
			link.l1 = "Neden burada bu kadar çok insan var...? Ve siz kimsiniz?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Beni kıyafetlerimden tanımıyor musun? Ve Genel Vali ile konuşurken sesine dikkat et! Hık!";
			link.l1 = "Demek siz Bay Van Diemen'siniz. Cahilce davranışım için özür dilerim. Burada bir karnaval mı var?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Aynen öyle, iyi adamım, başka yolu yok! Kadın kılığına girmiş bir karnaval! Ha-ha-ha! Fena değil, köylü! Eminim Luthers, Vette'in elbisesini giymeye bayııılırdı, ha ha ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "O zavallı koca müsveddesi, sevgili karısı başka biriyle yatarken gardıroptan gizlice bakmayı çok sever. Kadıncağızın da umurunda değil!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Değil mi, Vette, canım? Heh-heh.";
			link.l1 = "(Mandarin dilinde) Burada neler oluyor böyle...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hik! Ne dediğini anlamadım ama gözlerindeki bakıştan ve ses tonundan bana katıldığın belli! Van Haan tam bir sapık. Peki, sen nesin? Bir işçi mi? Yoksa Vette mi çağırdı seni?";
			link.l1 = "Ben...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Buraya bir işçi çağırmak bile Vette için fazla, bu adam belli ki kaybolmuş ve yanlış yerde. Hey, sen. Buradan defol ve gördüğün her şeyi unut. Kimin uşağısın? Onunla iletişime geçeceğiz, ikiniz de sessizliğiniz için para alacaksınız. Belki kıtadaki ailene dönmene bile izin verilir. Cevap ver ve git.";
			link.l1 = "Aslında, burada bir iş için bulunuyorum.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, işler. Burada “İş” yapan tek kişi Mynheer van Diemen. Benim görevim ise onu senin gibi insanlardan korumak. Luthers ise... her zamanki gibi. Yoksa... Vette seni gerçekten buraya davet etti mi?";
			link.l1 = " Hayır, ben buraya...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Sevgili Vette'm gerçekten buraya sarı suratlı birini mi davet ederdi?! Defol buradan!!!";
			link.l1 = "Zavallı aldatılmış adam...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Kimse seninle konuşmuyor. Çeneni kapa. Erkeklik taslama, onurun varmış gibi davranma.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Boynuzlu mu dedin?! Hayır, onu kendimden çok seviyorum. Ha, senin gibi aptal bir Çinli bunu anlayamaz zaten!";
			link.l1 = "(Mandarin dilinde) Hasta pislik.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Ho-ho-horoz mu?! Hiç sorun değil! Evet! Sadece biliyorum ki diğer adamlar sevgili Vette’me daha çok zevk veriyor, hepsi bu!";
			link.l1 = "Memleketimde derler ki, bir adamın tek bir parmağı kalsa bile hâlâ adamdır. Sen adam olsaydın, bunu anlardın.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Onu davet etmedim tabii ki, ama biliyorsun, oldukça iyi biri. Siz gittikten sonra da burada kalabilir. Köpeğimizle denemiştim ama hiç... ";
			link.l1 = "Kes sesini, erkekler konuşurken, orospu! Buradaki tek hayvan sensin. Ben buraya iş için geldim. Oliveiro Fermentelos'u arıyorum. Siz onun arkadaşları olmalısınız. Bana onun nerede olabileceğini söyleyebilir misiniz, Bay Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, bana hakaret etti! Bana hakaret etti! Bunu öylece bırakmayacaksın, değil mi?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, kusura bakma dostum, ama hanımefendi çok sinirli. Sana biraz görgü dersi vermem gerekecek. Birinci ders.";
			link.l1 = "Ama Oliveiro'yu arayışımda bana yardım edebilir misiniz?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Ölü bir işçiye faydası olmaz.";
			link.l1 = "(Mandarin dilinde) Hepinizin canı cehenneme...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(Mandarin dilinde) Kahretsin! Hiçbir şey öğrenemedim!";
			link.l1 = "(Mandarin dilinde) Bu günü asla unutmayacağım... Gardiyanlar gelmeden buradan çıkmam gerek. Gerçi bu akıl hastanesinden gelen seslere aldırış edeceklerini sanmıyorum...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(Mandarince) Tanrılar bu günü lanetledi! Van Diemen, uşağıyla uğraşırken kan kaybından öldü...!";
			link.l1 = "(Mandarin) Muhafızlar geliyor. Buradan savaşarak çıkmam gerekecek.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Ah, Chang Chang! Bu sefer neye ihtiyacın var, küçük dostum?";
			link.l1 = "Chang Tu bu... ne demek istiyorsun?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Benden nefret ettiğin her halinden belli, değil mi? Buraya gelmezdin, bir şeye ihtiyacın olmasa.";
			link.l1 = "Van Merden'in nerede olduğunu biliyor musun? Şehirde mi? Evde değil. Onunla konuşmam lazım.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Bir adamdan bütün gün evde oturup, tek bir sarı tenli adamın gelmesini beklemesi beklenemez. Adada işleri var. Bu gece şehre dönecek, o yüzden endişelenme, Chang Chang!";
			link.l1 = "Teşekkür ederim. Hoşça kal.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Hey, dar gözlü! Bu saatte nereye böyle aceleyle gidiyorsun? Şu an bütün düzgün insanlar çoktan uyumuştur.";
			link.l1 = "Peki ya sen?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Güzel söyledin! Devriyedeyiz! Duyduğuma göre, kasabada sarı tenli bir adam dolaşıp Allah'tan korkan insanları rahatsız ediyormuş.";
			link.l1 = "Kim olabilir bu, söyler misiniz?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Yeterince konuştuk - hava kararıyor ve uykum gelmeye başladı.";
			link.l1 = "Yakında uykun sonsuz olacak.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, iyi misin?";
			link.l1 = "Mynheer van Merden! Sayenizde iyiyim. Siz iyi misiniz? En önemli soru bu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Her zaman başkalarını düşünüyorsun, değil mi? Bu konuda ben de senin gibiyim. Sana saldırdıklarını gördüğümde, onları halledeceğini bilsem de öylece duramazdım. Soruna gelince, iyiyim, sadece biraz yorgunum. Bacaklarım biraz titriyor. Eğer sakıncası yoksa, içeri geçelim. Orada konuşuruz.";
			link.l1 = "Elbette, Mynheer van Merden, sonuçta burası sizin eviniz.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Artık acele etmeden, huzur ve sessizlik içinde konuşabiliriz. Söyle bakalım, seni bana getiren nedir, Chang Tu?";
			link.l1 = "Haklısınız, Mynheer van Merden. Batavia'dan yeni döndüm ve...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Bekleyin. Zavallı Chang Xing mi...?";
			link.l1 = "Hayır, hiç de değil! Umarım öyle değildir. Cennet hâlâ onun kaderini benden gizliyor. Fermentelos'a gelince... Batavia'da değil. Van Diemen hiçbir işe yaramadı.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Olmaz, çünkü o ve Oliveiro eski dostlar. İngilizlerin dediği gibi, suç ortağı ve arkadaş. Sana işe yarar bir şey verirse şaşırırım.";
			link.l1 = "Evet, hem size hem de Trust'a teşekkürler, güçlü silahlar edindim. Van Diemen'e saldırıp onu sorguya çekmek ve Fermentelos'un nerede olduğunu öğrenmek istedim. Ama hiçbir şey öğrenemeden öldü...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Etkileyici. İnsanların bildiklerini her zaman paylaşmak istemediğini fark etmişsin. Demek ki başka... ikna yöntemleri de var, öyle mi diyelim. Kız kardeşinin ölümünü öğrendiğini ve bu yüzden ortalığı kasıp kavurduğunu düşünmüştüm. Ama şimdi seni bana getiren ne? Sana Fermentelos'un nereye gittiğini bilmediğimi söylemiştim, Batavia'ya arada bir yaptığı ziyaretler dışında. Van Diemen de gittiğine göre, son ipucu da kayboldu.";
			link.l1 = "Ama siz birçok şey ve birçok insan biliyorsunuz. Belki yine yardım edersiniz diye düşündüm, Fermentelos hakkında etrafta sorabilirsiniz, tıpkı daha önceki gibi. Bana iyi davranan ilk beyaz adam sizdiniz. İlk... beyaz dostum.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Bu... dokunaklı.";
			link.l1 = "Mynheer van Merden, neden gülümsüyorsunuz...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Ha? Ah, affedersin Chang Tu. Yaşlandıkça duygusallaşıyor ve hüzünleniyorum. Bu içten bir gülümseme - saklayamadım. Beni dostun olarak görmene sevindim. Madem dostuz, arada bir bana da yardım etmeni beklerim. Karşılığında, Fermentelos konusunda sana kesinlikle yardım edeceğim. Merak etme - tuzağa düşmüyorsun.";
			link.l1 = "Hmm, size nasıl yardımcı olabilirim?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Son görüşmemizden bu yana, dilinizi ve kültürünüzü, özellikle de tıbbı daha derinlemesine inceledim. Zaman zaman bana bazı eski levhalar bulmanızı istiyorum. Her zamanki gibi cömertçe ödeyeceğim. Ayrıca arada sırada Çince konuşma pratiği de yapabilmeyi umuyorum. Hizmetkârlarımdan istemeye utanıyorum, ama bir dost...";
			link.l1 = "Chang Tu elinden gelenin en iyisini yapacak, Efendim van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Güzel. Önümüzde uzun bir yol var, dostum. Çok uzun bir yol. Ha! Sana iyi bir takma ad olurdu diye düşünüyorum. Benim işimde faydalı bir alışkanlık. Hollandalılar buna “Lange Afstand” der. İngilizler ise “Long Way.” Hangisini tercih edersin?";
			link.l1 = "İngilizce versiyonu daha çok hoşuma gidiyor. Long. Way. Longway. Benim dilimde kulağa oldukça uygun geliyor. Dinlediğiniz için teşekkür ederim, Lord van Merden. Longway emrinizi bekleyecek ve size yardımcı olmaya, isteklerinizi yerine getirmeye hazır olacak.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Arşiv demişken, Efendim Kaptanım, yanınızda mı? Sadece ona ihtiyacım var - şifreyi ezbere biliyorum.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Evet, sakladım, bir gün işe yarar diye düşündüm.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Maalesef, hayır. Kız kardeşini bulmak senin son umudun muydu?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway, Efendim Kaptan'ın endişelendiğine çok memnun oldu. Şimdilik hâlâ umut var. Guadeloupe'ta yeni bir iz buldum.";
			link.l1 = "Peki, o zaman. Orada sana ne oldu, anlat bakalım.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Bu akıllıca bir karardı. Belki orada Chang Xing'i arayışımızda bize yardımcı olabilecek bir şey buluruz.";
			link.l1 = "Bu harika olurdu. Hemen şimdi inceleyelim.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Evet, hadi birlikte inceleyelim. Yıl... 1637. Antoon van Diemen sattı... sattı...";
			link.l1 = "Köleler, değil mi?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Halkımdan kadınlar, zengin beyaz adamlara satıldı.";
			link.l1 = "Bu korkunç.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Efendim Kaptanım, hiç şaşırmış görünmüyorsunuz. O kadınların başına gelenler sizi hiç rahatsız etmiyor mu?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen yalnızca tamamen güvendiği kişilerle çalışırdı - sağ kolu Joep van der Vink ve o lanet olası Oliveiro Fermentelos. Ve... ve...";
			link.l1 = "Ne oldu? Sapsarı kesildin, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Çok üzgünüm. Bu korkunç bir şey, ama neden bu kadar şaşırdın? Daha önce Fermentelos'tan bahseden tüm sayfaları kopardığını söylemiştin. O zaman van Merden'den bahsedildiğini görmedin mi?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway aceleyle hareket ediyordu ve bu önemli ayrıntıyı kaçırmış olmalı.";
			link.l1 = "Anladım. Hazır olduğunda, hadi aramaya devam edelim ve şu anda işimize yarayacak ne varsa bulalım.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Fermentelos'un adamlarını kadınları yakalamak için gönderdiği, onları değiştirip kayıtları yok ettiği yazıyor. Sonra Merden onları Batavia'ya gönderiyor, orada van der Vink ve van Diemen kadınlarımızı beyaz adamlara satıyorlarmış. Keşke bunu daha önce öğrenmiş olsaydım...";
			link.l1 = "Yani, sonunda hepsi birlikte çalışmışlar. Kendini suçlama, Longway. Bunu bilemezdin. Arşiv daha yeni eline geçti. Başka bir şey var mı?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Evet. Neredeyse on yıldır böyle devam ediyorlar. O kadar çok kadın ailesini, onurunu, umudunu kaybetti ki... Ama sonra Fermentelos, van Merden'le çalışmayı bıraktı. Bana yardım etmesinin tek sebebi buydu - tek istediği eski ortağından kurtulmaktı.";
			link.l1 = "Burada onların başka hangi kirli işleri kaydedilmiş?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Van Merden'in karanlık düşüncelerinden daha fazlası. Van Diemen'in onu paradan çaldığını öğrenmiş. Bu yüzden beni Batavia'ya gönderdi; hem orada öleyim diye hem de van Diemen'i de beraberimde götürmemi umarak.";
			link.l1 = "Soğuk. Ama aynı zamanda inanılmaz derecede zeki.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Daha da kötü olabilirdi. O haydutları evine gönderip beni öldürmeye çalışan van Merden'di. Ancak onları kendi başıma alt edebileceğimi anlayınca yardım etmeye karar verdi.";
			link.l1 = "Her şeyi en ince ayrıntısına kadar düşünmüştü, hiç şüphe yok.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Hayatta döndüğümde, gerçek niyetini anladığımı ve intikam almaya geldiğimi düşünmüş olmalı. Konuşurken tabancasını masanın altında bana doğrultmuştu. Ama ona ilk beyaz dostum dediğimde... neredeyse kahkahadan patlayacaktı...";
			link.l1 = "Bu korkunç bir şey, Longway. Arkadaş sandıklarımızın aslında arkamızdan güldüğünü fark etmek çok acı.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway uzun zaman önce, bu takımadalara gelmeden hemen önce bir şey öğrendi. Portekizliler tarafından yakalandım ve beni asmak istediler. Lord Rodenburg hayatımı kurtardı.";
			link.l1 = "Onun hizmetine böyle mi girdiniz? Lucas da Formosa'da mıydı?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Evet, doğru. Hem de sadece o değil - Van Berg de var. Van Merden bana, Rodenburg'a beni bağışlamasını tavsiye edenin o olduğunu söylemişti. Ama bir süre sonra Longway, karanlık bir kaynaktan, aslında Portekizlileri peşime salanın Johan olduğunu öğrendi. O zaman inanmamıştım... ama şimdi bunun doğru olabileceğini anlıyorum...";
			link.l1 = "İğrenç.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Yine de, o gün kalbime şüpheler düştü. Bu yüzden Efendim Kaptanım ile van Merden'in karşı karşıya geldiğini öğrendiğimde, Longway sizin iyiliğinizi hatırladı ve sizin tarafınızı tuttu.";
			link.l1 = "Doğru kararı verdin, Longway. Heh, demek ki bunca zaman senin ilk gerçek beyaz dostun benmişim.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Öyleymiş, Efendim Kaptanım. Şimdi anlıyorum. Van Merden bana dostum dedi. Ama gerçekte, Longway onun için diğer işçilerden farksızdı – sadece çoğundan daha faydalıydım\nHepsi bu. Diğer sayfalar muhasebe ve Van Berg ile Rodenburg arasındaki ticari ayrıntılarla ilgili.";
			link.l1 = "Anladım. Şimdi de Guadeloupe'ta ne yaptığını anlatmanın zamanı geldi.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Sabah Yıldızı'nı arıyordum. Yırtılmış arşiv sayfalarından biri, en son St. Christopher yakınlarında görüldüğünü söylüyordu.";
			link.l1 = "Neden orada? Guadeloupe'ta buluşmak üzere anlaşmıştık ve seni orada buldum.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Çünkü St. Christopher's, van Merden'ın muhbirlerinden biri olan Georges Gravel'in evidir. Georges hâlâ Johan için çalıştığıma inanıyor. Ayrıca, Gravel bir zamanlar van Merden'a karşı ağır bir suç işlemişti. Ve Longway bunu örtbas etmeye yardım etti.";
			link.l1 = "Ve bu suç neydi?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Bu önemli değil. Önemli olan Georges'in Longway'e borçlu olmasıydı. Bu yüzden Gravel'in yardımcı rahip olarak çalıştığı kiliseye gittim. Efendim Kaptanım, devamını dinlemeye hazır mı? Biraz dalgın görünüyorsunuz.";
			link.l1 = "Affedersin, dalıp gitmişim. Evet, tabii, devam et Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "İyi, çok geç kalmadın. Burada gerekenden fazla kalmak istemem, biliyorsun! Bu sefer neye ihtiyacın var, Longway?";
			link.l1 = "Ses tonunu değiştir, Gravel. Kuruluş senin hizmetlerine ihtiyaç duyuyor.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "İtiraf etmeliyim ki, onlardan uzun zamandır haber alamadım. Beni unuttular mı acaba?";
			link.l1 = "Onlara hatırlatabilirim. Belki Lord van Merden'a ne yaptığınızı anlatarak.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Pekala, pekala, bu kadar sinirlenmene gerek yok! Sana nasıl yardımcı olabilirim?";
			link.l1 = "Morning Star hakkında bilgiye ihtiyacım var. Ne bulabilirsen getir. Ne kadar çok, o kadar iyi.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Tabii, ama bu zaman alacak! En az iki gün! En azından.";
			link.l1 = "Neden bu kadar uzun sürdü?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normalde, muhbirlerimin dilini çözmek için bağış kutusundan para alırım. Ama yakın zamanda soyulduk! Tabii ki Rahip yeni bir bağış toplama duyurusu yapacak, ama çatımızı da onarmamız gerekiyor - damlatıyor! Onu tamir etmek için çok fazla bağış gerekecek.";
			link.l1 = "İki gün. Burada sonsuza kadar kalamam. O kadar vaktim yok. Longway sabrıyla meşhur değildir. Lord van Merden ise ondan da az. Yoksa sana bunu hatırlatmamı ister misin, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Ulaşamayacağım şeyleri kontrol edemem! Elimden geleni yapacağım. Yine de, o haydutları bulup bağışlarımızı geri getirirseniz, çok daha çabuk öğrenirim!";
			link.l1 = "Düşüneceğim. Sen aramaya başla. İki gün. Daha fazla değil. Aynı saatte ve yerde buluşalım.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Bak hele! Adaya dar gözlü bir adam gelmiş! Efendilerinden mi kaçıyorsun, ha? Kimden saklanıyorsun, sorabilir miyim?";
			link.l1 = "Ben özgür bir adamım.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Eminim öylesindir. Ama güçlü ve akıllı görünüyorsun, gözlerin biraz çekik olsa da. Çetemize katılmak ister misin? Zaten gidecek başka bir yerin olduğunu sanmıyorum.";
			link.l1 = "Longway, onu ekibine katmaktan çok soymakla ilgilendiğini düşünüyor.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, kendini şanslı say. Geçenlerde şehirdeki bir kiliseyi soydum, inanabiliyor musun? Neden mi? Çünkü hırsızdan çalmak, gerçekten çalmak sayılmaz.";
			link.l1 = "Seni avlamayı düşünmüyordum, ama seni bulduğuma sevindim.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Bizi avlamaya mı geldin? Demek paralı askersin, kaçak bir işçi değil. O zaman senin için kötü haber.";
			link.l1 = "Aynen öyle.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Siktir... Neden beni hemen öldürmedin? Benden ne istiyorsun? Beni hapse mi sürükleyeceksin?";
				link.l1 = "Bununla ilgilenmiyorum. Sadece altını nereye sakladığını söyle.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Sarı suratlı piç...";
			link.l1 = "Longway'in sabrı tükeniyor. Zaten öğreneceğim. Tek soru, ne kadar acı çekeceğin.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Peki, tamam... Her şey bir mağarada. Para senin. Sadece... sadece beni öldürme, olur mu?";
			link.l1 = "Acı hiç olmayacak demedim ki...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(Mandarin) İşte haydutların saklandığı yer.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(Mandarin dilinde) Çok fazla!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(Mandarince) Ayak sesleri duyuyorum...";
			link.l1 = "(Mandarin dilinde) Burada başka biri var...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Biz burada ne halt ediyoruz? Kimse kalmadı - tüm haydutların gittiğinden emin olduk.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "İşte mesele bu, aptal! Geri dönecekler ve onlara sıcak bir karşılama yapacağız.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Etrafa bir bakayım, kimse saklanmıyor mu diye emin olayım. Zaten canım sıkılıyor...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(Mandarin dilinde) Askerler! Ne talihsizlik... Şimdi ne yapmam gerekiyor?";
			link.l1 = "(Mandarin dilinde) Bu paraya beyaz askerlerden daha çok ihtiyacım var! Onsuz gitmeyeceğim!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ah, Mösyö Longway, geri döndünüz!";
			link.l1 = "Elbette. Şüphe mi vardı? Morning Star hakkında bir şey bulabildin mi, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Evet, efendim. Ağır bir kalyon, kaptanı bir İspanyolmuş, öyle diyorlar...";
			link.l1 = "O Portekizli. Siz beyazlar birbirinizi bile ayırt edemiyorsunuz.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Ah, doğru. Benim hatam. Neyse, öğrendim ki gemiyi tüccar gemisi gibi göstermek için bayağı değiştirmiş; küçük kalibre toplar ve az sayıda mürettebat koymuş. Ama ambarı büyütmüş, ağzına kadar doldurmuş - o kadar ağır ki neredeyse zorla yüzüyor.";
			link.l1 = "Demek yeni bir hayata başlamak istemiş. Güzel. Şimdi, onu nerede bulabilirim?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Bu daha zor. Sürekli bizim kolonilerimizle İngilizlerin kolonileri arasında gidip geliyor, ama sadece Rüzgarlı Adalar'da. Yine de, şu anda büyük bir şarap yüküyle Basse-Terre'e doğru yola çıktığını öğrendim.";
			link.l1 = "Oraya nasıl hızlıca gideceğimi bulmam lazım.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Bu sizin sorununuz, Mösyö Longway. Benim kendi başıma yeterince derdim var... mesela şu lanet çatıyı tamir etmek gibi.";
			link.l1 = "Endişelerden bahsetmişken, o kilise soyguncularını buldum. İşte bağış paranız geri. Çatıyı onarın - Tanrınızın çatısız kalması hiç iyi olmaz.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Çok teşekkür ederim, Mösyö Longway! Bunu yapanın sen olacağını hiç düşünmemiştim.";
			link.l1 = "Ben de öyle düşünmemiştim. Ama o iki günü bir şekilde değerlendirmem gerekiyordu.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Yani, Guadeloupe'a gitmen mi gerekiyor? O tarafa giden bir gemi bulacağım sana. Yakında senden haber bekle!";
			link.l1 = "Bu çok yardımcı olurdu. Teşekkür ederim, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Georges’in bir tanıdığı olmalısınız? Bana bunu size vermemi söyledi.";
			link.l1 = "Bir not mu? Minnettarım. Bunun bana ait olduğunu nasıl anladınız?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Cidden mi?";
			link.l1 = "Ah, doğru.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Mektubu okur) Monsieur Longway, ‘Provence’ pinesi yarın sabah Basse-Terre’e hareket ediyor. Kaptan Mathieu Terugny’yi meyhanede bulabilirsin. Monsieur van Merden’a selamlarımı ilet. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Burada senin gibilerine içki vermiyoruz. Ve pirelerle ilgili şikayetler duymak istemiyorsam, sana oda da kiralamam.";
			link.l1 = "Bir içkiye ya da odaya ihtiyacım yok. Ve... Longway'in piresi yok.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Ben nereden bileyim lan? Hadi, söyle bakalım. Ne istiyorsun? O zaman defol.";
			link.l1 = "Yapacağım. Kaptan Mathieu Terugny'i arıyorum. Onu bir türlü bulamıyorum. Nerede olduğunu biliyor musunuz?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Gemiyle yelken açmaya hazırlanmakla meşgul, yerel dükkanda. Bu, senin gibi bir Çinliyle sohbet etmekten çok daha önemli, ama sen bunu belli ki anlamıyorsun.";
			link.l1 = "Aslında ben eskiden... Boşverin. Şu an önemli değil.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Ne istiyorsun, Çinli? Görmüyor musun, meşgulüm? Gemimi hazırlamam lazım.";
			link.l1 = "Kaptan Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Şaka olmaktan çıktı artık bu. Senin gibi biri benim kim olduğumu nereden biliyor? Seni biri mi gönderdi?";
			link.l1 = "Endişelenmene gerek yok. Basse-Terre'e gideceğini duydum. Beni de yolcu olarak alır mısın? Ücretimi öderim.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Bu iş gittikçe daha da ilginçleşiyor. Ben St. Pierre'e gidiyorum, Basse-Terre'e değil, ama küçük bir sapma olur. Bu iyi, çünkü seni gemide gereğinden fazla tutmak zorunda kalmayacağım. Beş bin peso. Üç saat sonra yola çıkıyoruz. Parayı iskelede ödeyeceksin. Tüccar olsam da pazarlık yok. Anlaşıldı mı?";
			link.l1 = "Evet. Teşekkür ederim. İskelenin orada görüşürüz, Kaptan Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Sonunda geldin demek, çekik gözlü. Senin gibilere kimse isteyerek gerçek para vermez diye düşünmüştüm.";
			link.l1 = "Beş bin peso, tam istediğiniz gibi. Yelken açmaya hazır mısınız?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Hayır, hayır! Aslında bunu sana sormalıydım. Ama anladığım kadarıyla hazırsın. Hadi bakalım. Sandalı sen kürekleyeceksin. Ve düzgün bir kamarada kalmayı bekleme! Bu yolu sırf senin için uzatıyoruz.";
			link.l1 = "Teselliye ihtiyacım yok. Sadece beni oraya götür.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...bu yüzden Longway Morning Star'ın tam olarak nereye gittiğini anlayamadı.";
			link.l1 = "Evet, o karmaşanın içine nasıl düştüğünü görebiliyorum.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Guadeloupe sularında bir brig gördüm. Belki de Banten'di. Öğrenmeye çalışacağım. Pekâlâ, şimdi gidebilirsin Longway. Bana getir "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Benim kaptanım, her şey yolunda mı? Longway bana sizi çağırdığınızı söyleyince hemen geldim.";
				link.l1 = "Sadece parçaları birleştirmeye çalışıyorum. Adanın açıklarında gördüğümüz o brigantinın adını hatırlıyor musun?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Beni görmek mi istediniz?";
				link.l1 = "Evet. Son zamanlarda gördüğümüz savaş gemisini hatırlıyor musunuz? Yerini ve adını öğrenin.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Hatırlıyorum, ama neden birdenbire bir brigaya ilgi duydun? Bunu öğrenmek biraz zaman alabilir.";
			link.l1 = "Helen, lütfen sadece yap. Ve evet, bunun biraz zaman alabileceğini biliyorum. Bekleyeceğim.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Hayır, bakmadım. Neden? Önemli mi?";
			link.l1 = "Hı hı. Daha fazlasını öğrenebilir misin? Şu anda nereye demirlediklerini bilmem gerek, eğer Guadeloupe sularından hâlâ ayrılmadılarsa.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Elbette. Sadece önceden söyleyeyim, biraz zaman alabilir. Bir sandal ve birkaç adam alıp yardıma gideceğim, di mi Charles?";
			link.l1 = "Elbette, Helen, teşekkür ederim. Bekliyor olacağım.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Efendim Kaptanım, beni mi çağırdınız?";
			link.l1 = "Evet, Alonso. Longway için geri döndüğümüzde adanın açıklarında bir brigadan geçtik. Adını öğrenme şansın oldu mu?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Hayır, benim görevim yeni katılanları gözetmek ve hücum birliğinde yer almak. Ayrıca, dürbünüm yok ve o kadar da yakın değildik.";
			link.l1 = "Doğru. Ama yine de öğrenmem gerek. Hallet bunu.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Evet, Kaptan. Sanırım bunu yarım günde halledebilirim.";
			link.l1 = "Acele et. Bekliyor olacağım.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Her şeyi öğrendim. Ben yokken her şey yolunda mıydı, benim kaptanım?";
				link.l1 = "Evet, iyiyim, teşekkür ederim, Helen. Söyle bakalım.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Oh, geri geldim. Gemini buldum.";
				link.l1 = "Tekrar hoş geldiniz. Nerede ve adı ne?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "Banten. Bu isim size bir şey ifade ediyor, değil mi? Şu anda deniz fenerinde, ve tayfasından birkaçı karaya çıktı. O gemiye saldıracak mıyız?";
			link.l1 = "Hayır, karaya tam olarak kimin çıktığını öğrenmemiz lazım. Karadan deniz fenerine gideceğiz. Zaten geciktik, limandan ayrılmamızın vakti geldi. Uzak bir yerde demirlemeliyiz. Capster Plajı iyi olur. Acele edelim, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Şey, brigantin adı Banten, ve şu anda fenerin yanında demirlemiş durumda. Mürettebatın bir kısmı da orada karaya çıktı. Ne yapacaksınız?";
			link.l1 = "Gerçeği öğrenmek için, deniz fenerine fark edilmeden ulaşmamız gerekiyor ve bunu ancak yürüyerek yapabiliriz. Gemimiz güvenli bir yerde demirlemeli. Capster Plajı nasıl olur?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "İyi fikir. Charles, seninle deniz fenerine gitmemi ister misin?";
			link.l1 = "Bunu gemiyi hareket ettirirken düşüneceğim - zaten yeterince yorgunsun.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "İşim biter bitmez geri geldim, Efendim Kaptanım.";
			link.l1 = "Çok iyi. Rapor ver, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "Kalyon hala adanın açıklarında – daha doğrusu, deniz fenerinin orada. Kıçında yazan isim Banten. Mürettebatlarından birkaçı karaya çıktı.";
			link.l1 = "İyi iş çıkardın, Alonso. Mürettebatı hemen demir almaya hazırla.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Sen de güverteye çıkmaya hazır mısın?";
			link.l1 = "Henüz değil. Eğer onların kaptanı deniz fenerine gidiyorsa, biz denizde saldırırsak şehirde saklanabilir. Gemimizi güvenceye almak için Capster Plajı'na gideceğiz, sonra deniz fenerine yaya yaklaşacağız.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Efendim Kaptanım, bakın! Fenerde birisi var.";
			link.l1 = "Güzel, tam zamanında geldik! Acele edelim ve onları yakalayalım. Alonso'nun bugün çok işi olacak.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Ama ya bu süreçte ölürlerse?";
			link.l1 = "Ne önerirsiniz?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = " Sessizce içeri süzülüp önce konuşmalarını dinleriz. ";
			link.l1 = "Bunu pencere tarafından görülmeden yapabileceğimizden şüpheliyim. Ama yine de deneyelim.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "HiddenImmortality");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Söylediklerimi düşün. İyice düşün. Para mesele değil - elbette belli bir sınır dahilinde. Ama o sınır bile sana altın dağları gibi görünecek - Çinli ölmeli! Daha önce adamlarımı onun peşine gönderdim, ama nafile. Fakat bu sefer, eğer senin adamlarınla birleşirlerse...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Bak, izleniyoruz! O! O ve lanet kaptanı!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Lanet olsun sana, pis Asyalı... Senin yüzünden o kadar çok şeye katlandım. Ve şimdi, tüm bunların sonunda, öleceğim...";
				link.l1 = "Sizi doktorumuza götüreceğiz, Efendim Komutan. Sadece kiminle konuştuğunuzu söyleyin - bu çok önemli.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Adı... Joep van der Vink, o... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Ölmüş... En azından adını biliyoruz. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Bu kesinlikle olamaz...";
			link.l1 = "Biraz solgun görünüyorsun, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway, on yıl önce van der Vink'i öldürdüğünden emindi\nKaçıyorlar! Gemileri çok hızlı!";
			link.l1 = "Evet, harika bir brig... ne yazık ki bizim için. Gemimize zamanında ulaşsak bile, yelkenleri açıp rüzgarı yakalayana kadar onlar çoktan gitmiş olurlar.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Bu son olabilir...";
			link.l1 = "Hayır, Longway. Beni dinle. Eğer Takımadalar'da kalmayı düşünüyorlarsa, er ya da geç onlarla karşılaşacağız – dünya küçük, Karayipler ise daha da küçük. İzlerini tekrar bulur bulmaz her şeyi bırakıp peşlerine düşeceğim. Sana söz veriyorum. Duydun mu beni?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Evet, Efendim Kaptanım. Teşekkür ederim.";
			link.l1 = "Başını dik tut, Longway. Gemiye aceleyle dönmemiz gerek – Komutan'ın ölümü çok yakında büyük bir haber olacak.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			ReturnOfficer_Longway();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur! Bir dakika! Siz kaptan mısınız?";
			link.l1 = "Belki. Nasıl tahmin ettin? Peki, ne istiyorsun?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Burada dağlardan ve sık ormandan başka bir şey yok – şehre giden yol da yok. Ama işte buradasın. Sadece gezmeye gelmedin, değil mi?";
			link.l1 = "İyi gözlem. Ama hâlâ ne istediğini söylemedin.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ah, doğru! Kaptan, gemimiz bu koyun hemen açıklarında kayalara çarptı. Sadece biz kurtulduk...";
			link.l1 = "Üzgünüm. Sizi bir yere götürmemi istiyorsunuz, değil mi?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Evet... Hiçbir sorun çıkarmayacağız, yemin ederim. Bizi sadece Belize'de bırak, gerisini biz hallederiz.";
			link.l1 = "Uzak değil, değil mi? O halde, gemiye hoş geldiniz.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Üzgünüm, ama ben başka yöne gidiyorum.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Teşekkür ederim, Kaptan! Kim bilir, sensiz daha ne kadar burada sıkışıp kalırdık.";
			link.l1 = "Elbette. Hiç vakit kaybetmeyelim!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Ama Belize çok yakın! Uzun sürmez, değil mi?";
			link.l1 = "Acelen var. Hiç oyalanacak vaktim yok.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Kısa bir yolculuk bile olmaz mı? Sadece Belize'ye? Lütfen, Kaptan, bizi burada bırakmayın!";
			link.l1 = "Pekala, umarım bundan pişman olmam. Herkes güverteye!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Güzel bir gün geçirmeniz dileğiyle, dostlarım.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Tekrar teşekkürler, Kaptan! Biz sadece sıradan denizcileriz, bu yüzden size sunacak pek bir şeyimiz yok.";
			link.l1 = "En azından yolumuzdan çok fazla sapmamıza gerek kalmadı.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Sağlığınıza kadeh kaldırır, kilisede sizin için bir mum yakarız.";
			link.l1 = "Hiç yoktan iyidir. Şerefe, dostlar!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Düydün mü? Sonunda onu yakaladılar! Sularımız artık nihayet güvende!";
			link.l1 = "Bu... iyi bir haber mi? Ama kimi yakalamışlar?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, bizzat Geveze'nin kendisi!";
			link.l1 = "Tanımıyorum - ne yaptı?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Sen bilmiyor musun?! Belli ki İngiliz değilsin, anlaşılıyor. O, yıllardır hem bizi hem de İspanyolları Seagull adlı gemisiyle yağmalayan bir korsan.";
			link.l1 = "Hem İngilizleri hem de İspanyolları yağmalamak mı? Bu alışılmadık bir şey.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Gerçekten öyle. Sahil muhafızları onu asla yakalayamadı, ama sonunda boyundan büyük işe kalkıştı – inanmazsınız, tuhaf bir tüccar gemisine yenildi.";
			link.l1 = "Bu komikmiş. Tüccarda tuhaf olan neydi?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Yani, yanında hiçbir koruması olmayan koca, hantal bir kalyondu! Ama o deli kaptanı sayesinde, Lutter bugün son şarkısını söyleyecek - asılmak üzere. Gelip görmelisin!";
			link.l1 = "Belki, ama şimdilik ilgilenmem gereken başka işlerim var.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Efendim Kaptanım!";
			link.l1 = "Bir İspanyol tüccarı cesur bir korsanı yendi... Longway’in düşündüğünü düşünüyorsun, değil mi?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "Sabah Yıldızı...";
			link.l1 = "Büyük ihtimalle - tüm takımadada onun gibi başka bir tüccar kaptan yoktur.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Hemen onu bulmalıyız!";
			link.l1 = "Doğru. Ama limanda ağır bir kalyon göremiyorum. Şu Geveze'yle asılmadan önce konuşmayı deneyelim. Bakalım o lakabı gerçekten hak etmiş mi.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			ReturnOfficer_Longway();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Hâlâ hayatta mı? Onunla konuşabilir miyiz?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Ne? Ah, evet. Hayatta - idam daha gerçekleşmedi. Onunla konuşabilirsin - her zamankinden daha konuşkan. Ama son zamanlarda saçmalıyor, çoğunlukla kendi kendine konuşuyor. Boşboğaz delirdi... Onu asmak için sabırsızlanıyorum, yoksa hepimiz onun bitmek bilmeyen gevezeliğinden delireceğiz.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Teşekkür ederim.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			ReturnOfficer_Longway();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Hazinemimi çaldı!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Hazinem artık ona bağlı, biliyorsun, ONA! Artık yapabileceğimiz hiçbir şey yok! Ne istiyorsun?! Bizden başka ne almak istiyorsun? Hiçbir şey kalmadı! O ölecek! Ya da daha kötüsü!";
			link.l1 = "Kim ölecek? Hangi hazine? Boşver, bu tamamen senin suçun - o kalyona saldıran sendin, tersi değil.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Hayır! Tam tersi oldu! Kahrolası hidalgo! Bizi bu belaya sokan o! Doğrudan üstümüze geldi ve yakından ateş etti! Sonra da onu elimizden aldı!";
			link.l1 = "Gerçekten mi? Bu şaşırtıcı değil. Onun hakkında başka ne anlatabilirsin? Ve... neyi aldı? 'O' kim?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "Anladım, zamanımı boşa harcıyorum...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Kaptan, izninizle... Lutter! Dışarı! Yolun sonu, dostum.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Kaptan, Sotta ve Lutter hakkında daha fazla şey öğrenmemiz lazım. Biraz soruşturalım.";
			link.l1 = "İyi fikir, Longway. Zaten o bağıran adamdan pek bir şey öğrenemedik.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Ama Sotta ile başlamak daha iyi.";
			link.l1 = "Evet, peşinde olduğumuz kişi o. Hadi gidelim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Hiçbir şey bilmiyorlar!";
			link.l1 = "Elbette. Ama artık kendi başımıza düşünmeye başlayacak kadar bilgiye sahibiz. Duyduğuma göre, Sotta ödül olarak aldığı o stratejik malları satmaya çalışacak, hem de yakında.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Aynen öyle!";
			link.l1 = "Onu Port Royal ya da Capsterville yolunda yakalamalıyız. Tek soru, nereye gittiği ve onu nerede karşılamamız gerektiği. Belki de açık denizde yakalarız.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Hayır! Longway demek istedi ki... Fermentelos deneyimli bir kaptan. Açık denizdeki bir savaş her türlü sonuçlanabilir. Limanda pusuya düşürürsek şansımız daha yüksek olurdu.";
			link.l1 = "Haklısınız, sanırım. Matt ile onun arasında gerçekten ne yaşanmış olursa olsun, Sotta tehlikeli ve asla hafife alınmamalı.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Biz de sabırsızlanıyoruz!";
			link.l1 = "Yine doğru söyledin, Longway. O halde hemen demir alalım, sonra bir sonraki hamlemizi planlarız.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Efendim Kaptanım, Sabah Yıldızı limanda!";
			link.l1 = "Evet, zaten fark ettim.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Planınız ne?";
			link.l1 = "Henüz karar vermedim. Kale toplarının altında onları ele geçirmeye çalışmak intihar olurdu. Ayrıca ağır gemilerini ele geçirsek bile onunla kaçamayız. Bir fikrin var mı, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Evet. Güvenli bir koyda demirleyip gece karanlığında sandalla kalyona yaklaşabiliriz.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "Half Moon Körfezi hakkında ne düşünüyorsun, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Bence Portland Cove uygun olurdu - yeterince yakın ve nispeten güvenli. Siz ne dersiniz?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Güzel seçim.";
			link.l1 = "Harika, anlaştık. Bir şeyi unuttuk mu?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Bence öyle değil, Efendim Kaptanım. Sadece iyi hazırlanmış olmamız gerekiyor.";
			link.l1 = "Kesinlikle.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Sen de kimsin lan, ne oluyor burada? Bay Holmes!";
			link.l1 = "Bay Holmes artık burada çalışmıyor. Ve tüm kapakları sıkıca mühürledik. Yani, bir süre rahatsız edilmeyeceğiz, Bay Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Ne? Fermentelos mu? Benim adım Edgardo Sotta!";
			link.l1 = "Hı hı, bunu daha önce de duymuştum. Gerçek adının bu olmadığını biliyoruz, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos öldü!";
			link.l1 = "Bir daha düşününce, gerçekten de fazla genç görünüyorsunuz. On yıl önce Morning Star'ın kaptanı olmanız mümkün değil. Peki, Oliveiro'ya ne oldu?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Ondan kurtulduk. O da bizim temizlememiz gereken bir sorundu - tıpkı yanında duran gibi.";
			link.l1 = "Pekala, Fermentelos olmadığınıza göre, belki yine de sorularımıza cevap verebilirsiniz. Arkadaşımın elinden aldığı birini arıyoruz.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Sana hiçbir şey söylemeyeceğim! Bunu yaparsam beni asla affetmez.";
			link.l1 = "Şu anda, asıl endişelenmen gereken şey bizim seni affedip affetmeyeceğimiz...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Sonunda öldü...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Ben Annabel Lutter. Tanrıya şükür, fazla bir şey yaşamak zorunda kalmadım, ama ilginiz için teşekkür ederim, bay...?";
			link.l1 = "Kaptan Charles de Maure. Lutter diyorsunuz...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, Matt'i duymuş olmalısınız? Zavallı aptal... Ben onun... sevgilisiydim.";
			link.l1 = "Kusura bakmayın, Bayan Lutter. Artık bir dul oldunuz. Kızlık soyadınız neydi, eğer bir sır değilse?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Benim hiç olmadı. Bana daha dikkatli bak. Zavallı annem korsanlara kölelik yapan koyu tenli bir kızdı. Babamın kim olduğu bilinmiyor, bu yüzden bana doğru düzgün bir isim vermeye bile zahmet etmediler.";
			link.l1 = "O zaman neden kimse sana dokunmadı? Yanlış anlama – böyle olmadığına sevindim. Ama yine de, bu... alışılmadık bir durum.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Öhö, ben de şımartılmaktan hoşlanmam. Ama devam et lütfen. Neden tayfa köle kızın kızına dokunmadı? Babanı tanımıyorsun ve o da umursamıyor gibiydi.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Sanmıyorum. Matt'i bildiğine göre, bir süre Levasseur için çalıştığını da biliyor musun?";
			link.l1 = "Evet, Sabah Yıldızı'nı ararken bunu duydum. Ama bunun konuyla ne ilgisi var? Lütfen her şeyi anlat bana.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Hâlâ anlamıyorsun, değil mi? Görünen o ki, Levasseur'un... zevklerinden hiç haberin yok?";
			link.l1 = "Hayır, görmedim, ama yine de bunun ne alakası var...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Ah, sanırım her şeyi anlatmam gerekecek. Eğer hassassanız, oturun lütfen, efendim. Şöyle ki, kendisi birçok kadınla birlikte oluyor ve...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Karısı ondan pek uzak değil, üstelik neredeyse herkesle yatıyor.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Ah hayır.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Bilirsin ya, derler ki... nasılsa koca, öyle de karısı. Ama yok, eminim o bundan çok daha ileri gitmiştir.";
			link.l1 = "Ne kadar uzağa?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Alayınız burada yersiz, efendim. Neyden bahsettiğimiz hakkında hiçbir fikriniz yok.";
			link.l1 = "Peki, peki, özür dilerim. Devam et, lütfen.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Bu sadece eşini aldatmak değil. Kadınları istekleri dışında alıkoyuyor. Üstelik bu tek seferlik bir istismar da değil. Genç kızları kaçırıp sahip olduğu şarap mahzenlerinden birinde tutuyor.";
			link.l1 = "Yani düzenli olarak köle kızlar mı alıyor? Ve sen de onlardan biri mi olacaktın?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "İkincisi konusunda haklısınız. Ama, ne yazık ki, ilki için öyle değil. Ona köleler gerekmiyor. Levasseur delirmiş – kendine özgü bir şekilde, benim Matt’im gibi değil. François bir kadına tamamen sahip olmak istiyor, hem bedenine hem ruhuna. Ve elbette, bu aşk değildi. O, özgür kadınların iradesini kırmak istiyordu. Zamanla bakışlarının, davranışlarının ve konuşma tarzlarının nasıl değiştiğini izlemekten zevk alıyordu...";
			link.l1 = "İğrenç...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Sen zaten biraz hasta hissediyorsun. Bir de o kadınların neler yaşadığını hayal et. Bunların hepsini duydum, hem de sadece Matt’ten değil. Levasseur bir keresinde Portekizli bir soylu kadını...";
			link.l1 = "Sen gözlerini kaçırıp sessiz kaldın. Her şeyi anlat bize. Eski Dünya'da da, Takımadalar'da geçirdiğim zaman boyunca da her türden şeyi gördüm. Artık hiçbir şey beni şaşırtmıyor.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Durun, onun başına ne geldiğini bilmek istemiyorum. Umarım o kadınlar onun elinde fazla acı çekmemiştir.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Ama böyle bir şeyi hiç duymadınız. Umarım asla da görmezsiniz. Onu Levasseur'a götürdüklerinde hâlâ gururlu ve dimdikti, oysa Matt'in anlattığına göre, Levasseur'un adamları kocasının Campeche yakınlarındaki çiftliğini ele geçirdikten sonra onu Tortuga'ya kadar defalarca tecavüz etmişler - adamcağız ise o canavarlar iki dizinden vurunca kan kaybından ölmüş...";
			link.l1 = "Güçlü bir kadın... Ama Levasseur'un genellikle kendisi için istediği kadınlara dokunmadığını söylemiştiniz.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Özellikle istediği olanlara dokunulmadı. Ama Senora Leontina bir hediyeydi. Onlar için beklenmedik ve hoş bir sürprizdi. Bu yüzden kendilerini tutmadılar...";
			link.l1 = "Anlıyorum...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Sanırım... Matt, François'nin gözdesi olmuştu. Levasseur'un gizli eğlencelerinden birine davet edildi... Ziyafet sırasında korsanlardan biri kadınların azlığından şikayet etti. Levasseur güldü ve sonra...";
			link.l1 = "Ve sonra? Ne oldu?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...sonra onu dışarı çıkardılar. Bir tasma takmışlardı! Dövülmüş, sırtı çiziklerle dolu, gözleri bağlı ve ağzı kapalıydı. Ağzındaki bağı çıkardıklarında ise söylediği tek şey şuydu...";
			link.l1 = "Korkunç bir şey olmuştur, sanırım. Ona elinden gelen bütün lanetleri yağdırdı mı?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Keşke... Dona Leontina sadece fısıldadı, 'Efendim ne ister?'";
			link.l1 = "Sanırım midem bulanacak. Matt sana sonra ona ne olduğunu anlattı mı?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Tabii ki öldürüldü. Ama Levasseur'un elleriyle değil. Onu başıboş bir köpek gibi attı kenara. Kaptanlarından biri vurdu onu. Ölmeden önce, sadece bir kelime söyledi...";
			link.l1 = "Bir lanet mi? Bir dua mı?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Hayır. 'Teşekkür ederim...'";
			link.l1 = "Böylesine bir işkenceden sonra ölüme şükretmek... Kim bilir neler yaşadı... ve onun gibi daha niceleri o canavarın ininde...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur özellikle kölelerden ve koyu tenli kadınlardan nefret ederdi - onlarda kıracak bir şey olmadığını söylerdi. Onlar onun yanında uzun süre dayanamazdı, Kızılderililer de öyle - birkaç inatçı hariç. Ama vahşilik ya da isyan da çözüm değildi - ona çabucak yaranmaya çalışanları da, fazla uzun süre karşı koyanları da öldürürdü.";
			link.l1 = "Bu korkunç... Söylesene, Levasseur'un yanında hiç Asyalı kadınlar oldu mu?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Hayır, en azından benim duyduğum kadarıyla yok. Bana gelince... Sana zaten söylemiştim, o esmer kadınlardan hoşlanmazdı. Matt, Francois için çalışırken benimle Tortuga sokaklarında açıkça dolaşırdı. Hatta bir keresinde beni konağa bile götürmüştü.";
			link.l1 = "Ama Levasseur seni yine de kölelerinden biri yapmak istemiş...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Kesinlikle... Neden beni bu kadar çok sevdiğini bilmiyorum... Matt öğrendiğinde, ona söylenir söylenmez adadan kaçtı. Bir daha asla Tortuga'ya dönmedi. Belki biraz deliydi, ama beni seviyordu. Bana hazinesi derdi...";
			link.l1 = "Demek Sotta'nın hazinesini ondan aldığını söylemesiyle bunu kastetmiş!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, öyle mi dedi? Ah, Matt... Ama galiba birlikte yaşlanmamız hiç mümkün değildi. Levasseur bir kadına göz koyduysa, geçmişi ya da bedeli ne olursa olsun, onu elde etmek için her şeyi yapardı. Sotta onun kaptanlarından biriydi ve ona ne denirse onu yapardı.";
			link.l1 = "Anladım. Peki şimdi ne yapmayı düşünüyorsun, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Kaçmak. Levasseur'un adamlarının bana ulaşamayacağı bir yere gitmek. Adımı değiştirmek. Kendimi gizlemek...";
			link.l1 = "Başarılı olmanı dilerim. Sana en iyisini diliyorum, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Yolculuk ayarlamak için paraya ihtiyacın olacak. Al bunu. Burada on bin peso var.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Sana biraz paradan fazlası gerekecek. Herkes koyu tenli bir kıza, melez bile olsa, yardım etmeye yanaşmaz. Al, burada yüz dublon var - bir gemi bul ve saklan.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Sen de! Hoşça kal, Kaptan.";
			link.l1 = "Hoşça kal.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Ben... Ne diyeceğimi bilmiyorum. Matt dışında kimse bana böyle bir iyilik göstermemişti.";
			link.l1 = "Belki de bu bir işarettir. Sonunda bir yerlerde mutlu bir şekilde yaşlanacaksın. Elveda.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Haklısınız. Bunun için size minnettarım. Hayatımın geri kalanında dualarımda sizi anacağım.";
			link.l1 = "Teşekkür ederim. Yolun açık olsun.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "O adam... Hayır, artık bir adam değil. O bir canavar. Kadınlara böyle işkence eden bir yaratık...";
			link.l1 = "Ne düşündüğünü biliyorum, Longway. Ama duydun - o hiç sarı tenli bir kadınla olmadı.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Ama o, grubun tamamını tanıyordu! Van der Vink, Fermentelos, Sotta... Az önce günlüğünde okuduk. Ya o bahsedilen 'o', aslında... onun kendisiyse?";
			link.l1 = "Kim bilir... Fermentelos'tan intikam almak isteyen bir kadın - böyle düşünmen çok doğal. Ama bu, Oliveiro tarafından hayatı mahvolan herhangi bir kadın da olabilir. Senin kız kardeşin olmak zorunda değil. Hatta sarı tenli bir kadın bile olmak zorunda değil.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Yani... bunu denemekten vaz mı geçiyorsunuz, Efendim Kaptanım? Tam da son anda...?";
			link.l1 = "Hayır, Longway. Ama bunu nasıl hayal ediyorsun? Levasseur'un sorularımızdan herhangi birine cevap vereceği pek olası değil. Ve Tortuga'da böyle dolanmak da fazlasıyla tehlikeli.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Peki, ne öneriyorsunuz?";
			link.l1 = "Bekleyelim. Levasseur'un senin kız kardeşin gibi kadınlardan hoşlanmadığını biliyoruz. Şimdilik kaynaklarımızı koruyabiliriz. Sabır ve güç. François kolay lokma değil, hele de o 'kaplumbağası' yüzünden. Ama Svenson'un yardımıyla, onunla kendi şartlarımızda konuşabiliriz. Sana kız kardeşini bulmana yardım edeceğime söz verdim ve bu sözümü tutmak istiyorum. Bana inanıyor musun, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Peki efendim Kaptanım. Ama Longway'in sizden bir isteği daha var.";
			link.l1 = "Ne oldu? Yine kendi başına gitmeyi düşünmüyorsun, değil mi? Geçen sefer pek iyi bitmemişti.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Hiç de değil, Efendim Kaptanım. Şimdi anlıyorum ki, ne yazık ki, benim gibi bir adam bu beyaz adamların yönettiği dünyada tek başına hiçbir şey yapamaz. Longway sizden Capsterville'e yanaşıp Georges Gravel'a bir not iletmenizi istiyor, hazırlıklarınızı yaparken ondan bir şeyler öğrenmesini rica ediyor.";
			link.l1 = "Akıllıca bir fikir, Longway. Öyle yapacağız.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Efendim Kaptanım, Longway'in sorması gereken bir şey var...";
			link.l1 = "Mektubu yazmayı unuttun mu? Gravel ile konuşabilirsin.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Hayır, mektup hazır. Ama Longway, şehirde tek başına dolaşmamak en iyisi olur diye düşündü. Efendim Kaptanım... mektubu Georges'a benim için iletebilir misiniz? Lütfen?";
			link.l1 = "Sana ben bir ulak mı görünüyorum? Yoksa burada kaptan sen misin?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Efendim Kaptanım...";
			link.l1 = "Ha ha ha, sadece şaka yapıyorum, Longway! Şu Gravel denen adamını nerede bulacağımı tekrar hatırlatır mısın?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Kilisede çalışıyor.";
			link.l1 = "Tamam, hallederim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, sevgili Charles, bir şey mi oldu? Endişeli ve... yorgun görünüyorsun, di mi?";
			link.l1 = "Ah, hayır, hayır, Mary, iyiyim. Sadece... şu Tortuga meselesi var ya. Yine çıkmaza girmiş gibi görünüyor... bir kez daha. Bir de şu Sharp'ın vasiyeti var ya, vallahi beni bayağı yıprattı. Ama boşver.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Ne? Ne görevi? Ve bunun Sharp'la ne ilgisi var? Hiçbir şey anlamıyorum!";
			link.l1 = "Çok fazla soru sordun, Mary. Burası böyle konuşmalar için uygun bir yer değil. Bunu meyhanedeki odada konuşalım mı? Senin sevdiğin gibi, gözlerden ve akıllardan uzakta. Son bir yılda neler yaptığımı sana orada anlatırım.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Tamam! Ama şunu bil: bir şey saklıyorsan...";
			link.l1 = "Kesinlikle hayır! Hadi gidelim, zaten öldürecek vaktimiz var...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Ne garip, değil mi Charles? Bu adanın sahibi olmam gerekiyormuş, ama hiç sahipmişim gibi hissetmiyorum.";
			link.l1 = "Sence?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Ah, şu gülümsemen... Bir kadına nasıl davranılacağını biliyorsun. Ama sana ne oldu? Yüzün bir tuhaf görünüyor!";
			link.l1 = "Neden? Bu benim her zamanki yüzüm, hem de çok yakışıklı.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, sesinden anlıyorum - son zamanlarda keyfin yok.";
			link.l1 = "Özellikle Longway'le uğraşırken başım dertte, üstümde çok yük var. Gerçekten çok yoruldum. Ama artık pes etmek için çok geç, özellikle de ona ve babama söz verdikten sonra.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Anlamıyorum... Longway'in bununla ne ilgisi var? Ve ne sözler verdin?";
			link.l1 = "Eğer bunu konuşacaksak, gelin meyhaneye gidelim, bir oda tutalım. Başkalarından uzakta.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Pekâlâ, hadi gidelim. Zaten yapacak başka bir şey yok, en azından biraz vakit geçirmiş oluruz birlikte.";
			link.l1 = "Yol göster, canım!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Birbirlerinin kollarında ne kadar huzurla uyuyorlar! Ne güzel!";
				link.l1 = "Kıskandın mı?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Haydi kalkın! Nasıl uyudunuz, aşk kuşları?";
				link.l1 = "İyiyim, sorduğun için teşekkürler. Peki siz çocuklar nasıl uyudunuz?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Bu saçma bir soru, sence de öyle değil mi?";
				link.l1 = "Öyle. Ve senin yaptığın da aptalca bir şeydi. Nedenini bilmek ister misin?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Senin keskin bir dilin olduğunu söylüyorlar, Charles de Maure.";
				link.l1 = "Ve sadece dilim değil. Öğrenmek ister misin? Ama söyle bana, neden biz uyurken saldırmadın?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ve neden böyle?";
				link.l1 = "Sabahları Mary'yi kızdırmamalısın. Nedenini yakında anlarsın.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Basit! Biliyorsun, karanlıktı, o yüzden hanginiz kızdı, anlayamadık.";
				link.l1 = "Orospu çocuğu.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Senden farklı olarak, ben kadınlardan korkmam. Lafı gelmişken - çocuklar, onu sağ salim götürün, yoksa Hugenot bizi kadın yapar!";
				link.l1 = "Hu... kim?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "En azından ben bir adama benziyorum. Çocuklar, sarışını canlı yakalayın - Huguenot onu bekliyor.";
				link.l1 = "Hu... kim?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Kimdi o, Charles? Kim bu lanet Huguenot? Yoksa gerçekten...?";
				link.l1 = "Bir tane var, Mary. Ve en iyisi...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... bu da neydi? Huguenot mu? Bu düşündüğüm adam mı gerçekten?";
				link.l1 = "Korkarım öyle, Helen. Devam etmemiz gerekiyor...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = " Duyuyor musun? Birileri geliyor, di mi. Muhtemelen şu ölülerin dostları.";
				link.l1 = "O zaman onların yanına katıldıklarını göreceğiz. Hazırlan...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Bunu duyuyor musun? Ayak sesleri.";
				link.l1 = "Elbette biliyorum. Arkamda durun.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Efendim Kaptanım, hanımefendi "+sStr+".";
			link.l1 = "Longway?! Odamıza böyle pat diye girebileceğini mi sandın? Ya biz...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, affedersiniz, Efendim Kaptanım. Böyle meşgul olsaydınız kapıyı kapatmış olurdunuz diye düşündüm. Ama Longway açık buldu.";
			link.l1 = "Kırık, ama açık değil. Ama söyle bana, dostum, neden bu kadar lanet olası sakin görünüyorsun? Yerde cesetler var, biz silahlıyız ve sen...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Alışkınım zaten.";
			link.l1 = "Ve buna karşı çıkamazsın, değil mi? Ama gerçekten, buraya gelirken dövüş seslerini duymadın mı? Bu heriflerin meyhaneye girip gözünün önünde yukarı çıktıklarını görmedin mi? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Hayır, Efendim Kaptanım. Buraya çıkarken salonda hiç yabancı görmedim.";
			link.l1 = "Bu gerçekten tuhaf bir tesadüf. Peki ne istiyorsun, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Acilen bir gemiye ve mürettebata ihtiyacım var, Efendim Kaptanım.";
			link.l1 = "Ne? Neden? Sonunda Chang Xing'in izini mi buldun? Öyleyse, hemen şimdi birlikte peşine düşelim.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Ne yazık ki Chang Xing değil. O... Joep van der Vink. Georges Gravel bir mesaj gönderdi ve ben onu köyde dolaşırken aldım, siz ise... hanımefendiyle dinleniyordunuz.";
			link.l1 = "Evet, gerçekten iyi dinlendim, bunu söyleyebilirim. Ama neden şimdi ayrılalım, Longway? Bitirmemiz gereken bir sürü önemli iş ve öldürmemiz gereken tehlikeli insanlar var.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink, Levasseur kadar tehlikeli değil. Ayrıca, onu zaten bir kez yendim. Ve yine yeneceğim. Bu sefer, gerçekten öldüğünden emin olmak için. Hepimizin onunla vakit kaybetmesini istemiyorum. Siz Tortuga'ya gidip önemli kişilerden ihtiyacımız olan şeyleri sorun. Van der Vink'i ben yakalayacağım. Efendim Kaptanım, bu sizin zamanınızı harcamaya değmez ve ben de bir zamanlar kaptandım. Hallederim.";
			link.l1 = "Hmm, haklısın Longway. Van der Vink o kadar tehlikeli olmayabilir, ama 'Banten' takımadadaki en hızlı gemilerden biri. Onu yakalamak için her gemi uygun olmaz. Peki ya mürettebat? Adamları bu kadar çabuk ve tek başına nasıl toplamayı düşünüyorsun?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Doğru yeri biliyorum ve orada Şirket'in itibarına sahibim. Ya da en azından Georges'a yaptığım gibi öyleymiş gibi davranabilirim. Şirket... Bay Rodenburg acil olarak savaşçı adamlara, profesyonel mürettebata ihtiyaç duyduğunda onların hizmetlerinden yararlandı, sorgusuz sualsiz çalışan adamlara.";
			link.l1 = "Demek gemi mürettebatı kiralanabiliyor... Böyle bir şeyin olması mantıklı. Peki, bunun bedeli ne kadar olacak?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "İki bin beş yüz. Hemen, şimdi ve burada.";
			link.l1 = "Hepsi bu mu? Bir meyhaneden sıradan tayfaları tam kadro toplamak bundan fazlasını ister, hele ki büyük bir gemi için. Görünen o ki, Rodenburg ve adamlarının özel yerlerde özel fiyatları var.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Altınlardan bahsediyordum, Efendim Kaptanım.";
			link.l1 = "NE?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Beni doğru duydunuz, Efendim Kaptanım. Bu önemli. Böyle bir miktarı önemsiz bir şey için istemem.";
			link.l1 = "Evet, seni duydum, ama hâlâ inanamıyorum. Gerçekten de özel fiyatlar. Peso kabul ediyorlar mı?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Evet... beyazlardan. Longway için bu zor olabilir, ama... yeterince ısrar edersem onları ikna edebileceğimi düşünüyorum. Her zaman bir yol vardır.";
			link.l1 = "Eh, bu da bir şey. Ve bu sadece mürettebat için... Bir de gitmen gereken bir gemi var. O da muhtemelen 'özel bir yerde', değil mi? Kaç paraya mal olacak, sormaya bile korkuyorum...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Tam olarak öyle değil, Efendim Kaptanım. Mürettebat kendi gemisiyle gelir.";
			link.l1 = "Ama?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "'Meifeng'. O, Karayipler'de ondan hızlı bir gemi yok; bu yüzden belirleyici bir faktör olabilir. Ve o... o bana aitti, yani onu iyi tanırım. Onu bana ödünç verir misiniz, Efendim Kaptanım?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Al. İki buçuk bin dublon. Yeter ki bana van der Vink'in kafasını altından bir tepside getir, ha ha ha ha!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Yanımda o kadar çok doblon taşımıyorum, Longway. Ve gemide bile o kadar olacağını sanmıyorum - bahsettiğin şey bir yığın altın. Ama peso, tabii. Üç yüz bin tam da ihtiyacın olan miktar.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Biliyor musun Longway... Gerçekten de sıradan bir hayduta karşı savaşasın diye bir kuşatma filosunu donatacak kadar para ödememi mi öneriyorsun?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Ah... Longway kalbinin derinliklerinden teşekkür ediyor, Efendim Kaptanım! Ama yine de, ya 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "O ne olacak? Dostum, buraya gelirken kafanı mı çarptın? Şu anda filomuzda, biliyorsun!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Bunu düşünmem lazım, Longway.  Van der Vink'i yakalamak için ne kadar vaktimiz var?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Efendim Kaptanım, ufak bir hata yaptınız. İki yüz elli bin peso olacaktı.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Çok teşekkür ederim, Efendim Kaptan... Ama, ya 'Meifeng' ne olacak?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "O ne olacak? Dostum, buraya gelirken kafanı mı çarptın? Şu anda filomuzda, biliyorsun!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Bunu düşünmem lazım, Longway.  Van der Vink'i yakalamak için ne kadar vaktimiz var?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Başka yolu yok, Efendim Kaptanım, lütfen sakin olun...";
			link.l1 = "Ah, henüz başlamadım. Anlaşma şöyle. Elli bin peso. Bu, tersaneden bir brig almak, onu savaşa hazırlamak ve hatta bir mürettebat tutmak için tam yeterli.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			Notification_Approve(false, "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Ama, Efendim Kaptanım. Bu bir beyaz kaptan için yeterli olabilir! Herkes Longway ile iş yapmaya razı olmaz. Bana bir şey satmadan önce sıkı pazarlık yapacaklardır!";
			link.l1 = "O halde, ikna edici olun! Başlangıçtaki... teklifinize bakılırsa pazarlıkta oldukça ustasınız. Hâlâ burada mısınız? Madem bu kadar acil diyorsunuz, alın şu parayı ve gidin!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Başüstüne, Efendim Kaptanım...";
			link.l1 = "Bana öyle bakma. Sonra Tortuga'da görüşürüz. İyi şanslar.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Öhöm, hayır, Efendim Kaptanım. Elbette, hatırlıyorum. Longway sadece onu benimle paylaşmaya hazır olup olmadığınızı soruyordu.";
			link.l1 = "Evet, öyleyim. Sonuçta, van der Vink kız kardeşinizin başına gelenlerde listemizdeki diğerleri kadar suçlu. Onu yakalamak gerçekten çok önemli. Meifeng’in komutasını size veriyorum.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "İnanamıyorum... Teşekkür ederim, Efendim Kaptanım!";
			link.l1 = "Ah, önemli değil. O eskiden senin gemindi, bunu her zaman hatırlayacağım. Neyse, devam et. O kahrolasıyı öldür. Ben Tortuga'ya gidiyorum.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			Notification_Approve(true, "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Zaman dar, Efendim Kaptanım. Boşa harcamamalıyız - Chang Xing bizim yardımımıza ihtiyaç duyabilir...";
			link.l1 = "Bunu biliyorum, Longway. Yine de, van der Vink'i yakalamak için tam olarak ne kadar vaktimiz var?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Birkaç ay - o kadar süre boyunca düzenli rotasında gider, sonra bir süreliğine ortadan kaybolur. Onun tarzı böyle, Gravel bana mektubunda öyle yazmıştı.";
			link.l1 = "Pekala. O zaman gemiye gidelim...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Korkarım hazırlıklarıma hemen başlamam gerekecek, Efendim Kaptanım. Meifeng elimde olur olmaz vakit kaybetmeden başlayabilelim diye. Adamlarla önceden konuşmam lazım. ";
			link.l1 = "Peki, nerede buluşuyoruz?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Tam burada. Ama isterseniz, sizin için uygun olursa, tersanede de buluşabiliriz.";
				link.l1 = "Ve neden burada, doğru parayı verince tam teşekküllü bir savaşçı tayfası tutulabileceğini bilmeyen tek kişi benmişim?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "O paralı askerlerin eskiden Isla Tesoro'da bir yerleri vardı, ama buraya taşınmak zorunda kaldılar.";
				link.l1 = "Nedenini anlayabiliyorum. Peki, La Vega'da seni nerede bulabilirim?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Çünkü bunu çok az kişi biliyor. Ve daha da azı bunu karşılayabiliyor. Mynheer Rodenburg uzun süre onların tek müşterisiydi.";
			link.l1 = "Anladım. Tamam, Longway. Orada görüşürüz.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "Meyhane, Efendim Kaptanım. Başka nerede olabilirdim ki?";
			link.l1 = "Doğru. O zaman sonra görüşürüz, Longway! Kendine iyi bak.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Efendim Kaptanım, size bildirmek isterim ki mürettebat hazır. Son bir mesele kaldı. 'Meifeng' ne olacak?";
			link.l1 = "Şimdiye kadar, sana layık bir gemi seçemedim, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"' senin.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "Ya 'Meifeng' ne olacak? Onu heba etmeme izin verdiğimi mi sandın?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Sana özel bir gemim var, Longway. Hızlı bir gemi. Ve Meifeng'den bile daha ölümcül. Bir savaş kalyonu, adı da 'Uçan Yürek'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Sen kırlangıçları seversin, Longway. Peki ya polaklar? Özellikle şu, 'Torero'. Yarışlar için yapılmamış tabii, ama oldukça güçlü bir gemi.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "İtiraf etmeliyim ki, bir gün bunun gerçekten işe yarayacağı aklıma gelmezdi. Bu kalyon hakkında ne düşünüyorsunuz? Kudretli 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Bu 'Meifeng' değil, Efendim Kaptanım! Meifeng'e ne oldu?";
			link.l1 = "Longway! "+sStr+" Tehlikede! Kız kardeşin de öyle! Ve sen böyle bir gemin olmadığı için huysuzlanıyorsun?! Herkes böyle bir gemiye sahip olsa mutlu olurdu! Al onu komutanlığının altına  ve van der Vink'e neler yapabileceğini göster.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Pekala... Umarım Cennet bana iyi bir talih yollar. Aynı şekilde, Tortuga'da size de aynısını dilerim. Hoşça kalın, Efendim Kaptanım.";
			link.l1 = "Bundan eminim. Hoşça kal, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Öhöm, hayır, Efendim Kaptanım. Elbette, hatırlıyorum. Longway sadece onu benimle paylaşmaya hazır olup olmadığınızı soruyordu.";
			link.l1 = "Ben de öyle düşünüyorum. Sonuçta, van der Vink kız kardeşinizin başına gelenlerde listemizdeki diğerleri kadar suçlu. Yani onu yakalamak gerçekten önemli. 'Meifeng'in komutasını size veriyorum.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "İnanamıyorum... Teşekkür ederim, Efendim Kaptanım!";
			link.l1 = "Ah, önemli değil. O eskiden senin gemindi, bunu hep hatırlayacağım. Neyse, devam et. O kahrolasıyı öldür. Ben Tortuga'ya gidiyorum.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			Notification_Approve(true, "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Ben... Ben BUNU yönetemem, Efendim Kaptanım. Longway hâlâ hayatını, ruhunu ve aklını önemsiyor.";
			link.l1 = "Ha ha ha, Longway! Hadi ama, bu kadar batıl inançlı olduğunu bilmiyordum. Ama neyse, lanet kalktı, artık korkacak bir şeyin yok.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... ama van der Vink bunu biliyor mu? O gemiyi görür görmez korkmuş bir tavşan gibi kaçacak.";
			link.l1 = "Haklısın bu konuda. Peki, senin için başka bir şey buluruz.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Kendi başıma kaptanlık yaparken hiç polacre kullanmadım. İlginç bir gemi, ama şu anda en önemli şey hız, güç değil.";
			link.l1 = "Doğru, ama sonuçta bu bir polakra. 'Banten' kadar hızlı olmayabilir, ama onların yakalayamayacağı açılardan rüzgarı yakalayabilirsin. Hatta 'Meifeng'in kendisinden bile daha iyi. Bunu avantaja çevir.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Yine de... 'Meifeng' daha iyiydi... Onu harcamana izin vermen yazık oldu, Efendim Kaptanım. Tortuga'da bol şans.";
			link.l1 = "Sana da, Longway. Teşekkür ederim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				Notification_Approve(true, "Longway");
			}
			
			dialog.text = "Bu, Takımadalar'daki en sıradışı kalyon olabilir, Efendim Kaptanım. Onunla başa çıkabilirim, ama 'Banten'den daha yavaş...";
			link.l1 = "Şey, Joep'le bir yelken yarışında yarışmıyorsun, değil mi?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Ne derseniz deyin. Ama 'Meifeng' daha iyiydi... Onu harcamana izin vermen yazık oldu, Efendim Kaptanım. Tortuga'da bol şans.";
			link.l1 = "Sana da, Longway. Teşekkür ederim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Endişeniz için teşekkür ederim, Efendim Kaptanım, ama lütfen acele edin - fazla vaktimiz yok.";
			link.l1 = "Biliyorum. Ama boşuna vakit kaybetmek istemezsin, değil mi? Tamam, sana düzgün bir gemi bulacağım.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Neredeyse geldik, Charles. Nereden başlayacağına karar verdin mi? Belki sokaktaki insanlara sormamız mantıklı olur...";
			link.l1 = "Belki öyledir. Ama bizim için değil - benim için. Sen gemide kalacaksın, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, elbette, o alçaklar ve söyledikleri hakkında hâlâ içim rahat değil, tayfanın koruması altında kalmam mantıklı... Ama sen canavarın inine tek başına gidiyorsun diye kendimi daha güvende hissetmiyorum.";
			link.l1 = "Anladım. Ama işler ters giderse, senin güvende olduğunu bilerek tek başıma kaçmak çok daha kolay. Bu bir emir, Helen. Beni burada bekle ve fazla endişelenmemeye çalış.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "İşte Tortuga, Charles, tamam mı. Sabırsızlanıyorum, kapıları çalıp o şişko eşeğin benden ne istediğini sormak için...";
			link.l1 = "İşte tam da bu yüzden gemide kalıyorsun, canım.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Olmaz! Sahile tek başına gitmene izin vereceğimi mi sanıyorsun?";
			link.l1 = "Bence Levasseur, paralı askerlerinin başaramadığını tamamlamaya karar verirse, karşı koyma şansımız olmaz. Onu gereksiz yere kışkırtmak istemiyorum, özellikle de hedefim o değil, Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Yani şimdi hapislerdeyim, di mi?";
			link.l1 = " Sana emir vermiyorum, senden rica ediyorum, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "Sana o lanet adanın arka sokaklarında bir şey olursa ne yaparım?";
			link.l1 = "O zaman söz veriyorum, kahramanlık yapmayacağım. Senin güvende olduğunu bilmek bana hız kazandırır. O yüzden gemide beni bekle, ne olursa olsun, Allah aşkına, karaya çıkma.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Sen kimsin? Sadece sohbet etmek için sahilde yürüdüğünden şüpheliyim.";
			link.l1 = "Evet, doğru. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Charles de Maure mu? Kahretsin, beni sakın karanlık işlere bulaştırma. Evet, benim. Peki, ne istiyorsun?";
			link.l1 = "Bana Joep van der Vink ile arkadaş olduğun söylendi, ve...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Bunu sana kim söyledi? Onun bağırsaklarını deşerim. Yani, birbirimizi tanıyoruz, hepsi bu. Sizinle arası bozulduğu için başıma iş almak istemem.";
			link.l1 = "Heh, arkadaşlarından vazgeçmekte ne kadar da hızlısın...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Bunu düşünme. Senden korkmuyorum. Ama neden zahmete gireyim ya da böyle bir mesele çıkarayım? Joep'i sana anlatıldığı kadar yakından tanımıyorum. Onu mu arıyorsun?";
			link.l1 = "Evet, bir bakıma. Onun Tortuga'dan çoktan ayrıldığını biliyorum ama hakkında daha fazla şey öğrenmek fena olmazdı — nerede bulunmuş, kimlerle konuşmuş. Bana yardımcı olabilir misin?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Sana zaten bir faydası olmazdı, o yüzden... neden olmasın? Bir genelevdeydi. O genelevde. Bunu karşılayabileceğini düşünüyorum, bu yüzden sana anlatıyorum.";
			link.l1 = "Yeni bir genelev mi? Artık bir tane yetmiyor mu sana?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Yani, yeni değil, ama pek kimse bilmiyor. Ve sadece az kişi karşılayabiliyor. Sanırım senin zamanın geldi. Ama uyarayım – sadece doblon geçerli. Gümüş uzatırsan, tekmeyi yersin.";
			link.l1 = "Öyle tahmin etmiştim. Peki, bu genelevin nerede olduğunu söylemiştin?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Şu sütunlu binayı biliyor musun? İşte orası. Bir de ne hostessleri var! Sarı tenli, öyle güzel ki! Hah, bakıyorum şimdiden ağzın sulandı, ha?";
			link.l1 = "Heh-heh, sayılır. Teşekkürler, Rober. Bugün senin için bir sorun yok - bana çok yardımcı oldun.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Sonunda döndün, Charles! Yerimde duramadım, di mi!";
			link.l1 = "Çok uzun sürmeyecek, Mary. Küçük bir işim var... Merakta bırakmayayım - Longway'in işiyle ilgili. Yerel bir geneleve uğramam gerekiyor.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Seni kıyıya tek başına bırakmamam gerektiğini biliyordum. Ya şapkanı takmayı unuttun, kafan güneşten ısındı... Ya da bir yere çarptın, di mi!";
			link.l1 = "Mary, beni dinle. Bu mekânın sahibi Longway'in kız kardeşi olabilir. Emin olmak için onu görmem gerek, ama sadece bunu yapacağım. İçeri girmeden bunu yapamam. Ama senin yanlış bir şey düşünmeni istemem.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Bana yalan söylemediğinden emin misin, Charles?";
			link.l1 = "Mary, şöyle düşün... Hiç bir adamın sevdiğini böyle bir şey hakkında uyardığını duydun mu...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Orada dur Charles, bunu düşünmek bile istemiyorum. Sana inanıyor ve güveniyorum. Ve umarım orada gerektiğinden fazla kalmazsın.";
			link.l1 = "Bir dakika bile daha değil, canım, söz veriyorum. Girip çıkacağız, göreceksin.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Beklediğimden bile daha çabuk döndünüz. Ama ne oldu? Pek iyi görünmüyorsunuz... Joep van der Vink hakkında bir şey öğrenebildiniz mi?";
			link.l1 = "Henüz değil. Birkaç şey öğrendim, ama daha ileri gitmek için... bir geneleve gitmem gerekiyor. Tabii ki düşündüğünüz şey için değil.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Bir genelev mi? Bu yerlerin apaçık olanın dışında başka bir şey sunduğunu bilmiyordum.";
			link.l1 = "Sadece sahibiyle konuşmam gerek, hepsi bu. Ve burası sıradan bir genelev değil. Söylentiye göre - burası yalnızca yüksek sosyete üyelerine açık, çok pahalı bir yer...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Pekala, o zaman tam sana göre, canım. Şaka yapıyorum tabii. Yine de oraya gideceğin için pek memnun değilim. Ama...";
			link.l1 = "Söz veriyorum, tamamen Longway'in işi için gidiyorum. Oranın sahibi muhtemelen onun kız kardeşi. Uzun kalmayacağım.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Nasıl istersen. Bana böyle şeyleri anlatmak zorunda değilsin. Sana başka bir adamla olmayacağıma dair hiç söz vermedim. Ama yine de yapmıyorum. Çünkü bu benim için zaten olması gereken bir şey.";
			link.l1 = "Başka koşullarda, seni de yanıma alırdım, ama...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Teşekkürler, ama istemem. Charles, endişelenme. Ben öyle aptal, kıskanç bir kız değilim. Yani, belki kıskancım, ama aptal değilim. Ve sana inanıyorum. Aptal ben!";
			link.l1 = "Teşekkürler, Helen. Hemen döneceğim.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Ah, işletmemizde yeni bir yüz mü? Hoş geldiniz, monsieur. Yiyecek, yıllanmış şarap, sıcak bir banyo - hepsi sizi bekliyor, tabii ki aramızdan biriyle vakit geçirecek kadar paranız varsa.";
			link.l1 = "Karşılama için teşekkür ederim, mademoiselle. Ama buraya bu yüzden gelmedim. Birini arıyorum...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Güzel. Bu sözleri daha önce hiç duymamıştım.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Biz burada sadece oyuncak değil, eğitimliyiz. Ev sahibesi bunun işletmemiz için çok önemli olduğunu düşünüyor.";
			link.l1 = "Ev sahibesi! Onu arıyorum. Sarı tenli olduğunu duydum. Söylesene, doğru mu? Bu arada, adı ne?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "Doğru. Ama birçok beyaz kadından daha iyi bir ticari zekâsı var. Adı Belle Etoile. Ama artık yeter, konuşmayalım.";
			link.l1 = "Yeterince konuştuk mu diyorsunuz? Ben buraya konuşmaya geldim. Birkaç soru daha soracağım, sonra gideceğim.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "Ve bunun işletmeye ne faydası var? Burada bedene değil, zamana para ödenir. Konuşmak mı istiyorsun? Buyur. Ama para peşin. Odada, meraklı kulaklardan uzakta fısıldaşırız. Orada ne yaptığımız umurumda değil - istersek mum yakıp dua edelim, bana fark etmez. Bir müşteri bir keresinde bana bir şiir yazmasına yardım etmemi istedi. Bir diğeri dertleşmek, beni iyi bir dostu olarak görmek istedi. Bir üçüncüsü ise... sadece mum yakmak, sonra da...";
			link.l1 = "Pekala, bilmek istemiyorum - zaten yakın zamanda hoş olmayan bir şey duydum. Sana ne kadar borçluyum?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "İki yüz elli dublon. Pazarlık yok. Eğer karşımızdakinin beş parasız bir sahtekar olduğunu anlarsak, hiç acımadan kapı dışarı ederiz. Zengin ama açgözlü çıkarsa, fiyatı yükseltiriz – nasıl olsa ödeyecek.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Buyurun, iki yüz elli altın.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Vay canına, burası Jamaika’daki genelevden bile daha pahalı. Altını bulduktan sonra geri gelebilir miyim?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Güzel. Nereden başlayalım? Akşam yemeği, mumlarla mı mumsuz mu, banyo, sohbet?";
			link.l1 = "Fazla vaktim yok, o yüzden sorularıma hemen geçelim. Yolu göster.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Elbette yapabilirsiniz. Sabır, bir saraylının erdemlerinden biridir. Bir dilenciyi dışarı atmak bir şeydir. Sizin gibi zengin bir beyefendinin gidip parasını almasına ya da hatta ödünç bulmasına izin vermek ise bambaşka bir şey.";
			link.l1 = "Bir fahişenin erdemleri... İronik. Hemen döneceğim.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Tekrar hoş geldiniz, monsieur! Peki, siz kimsiniz? Varlıklı bir beyefendi mi, yoksa bir gösterişçi mi?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Elbette, ben zengin bir centilmenim, mademoiselle. Altınlarınız burada - tam iki yüz elli doblon. Saymanıza gerek yok.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Hâlâ eksik kaldım, biraz sabret lütfen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Burada sayım yapmayız. Hmm, paraların bazıları yamulmuş ve kırık görünüyor - hanımefendi bundan pek hoşlanmaz, ama en azından hepsi gerçek altın.";
			link.l1 = "Ne kadar... zarif bir insan kendisi.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Doğru. Madam Etoile yeri geldiğinde yumuşak ve şefkatli olabilir, bazen serttir, bazen de acımasız. Bu yüzden biz sayılmayız, bu arada. Hanımefendiye her zaman hemen ödeme yapılmaz, ama hakkını mutlaka alır. Altınla değilse, kanla. Her genelevin koruyuculara ve hamilerine ihtiyacı vardır. Bizimkiler de mekanın itibarına yakışır.";
			link.l1 = "Ödedim, o yüzden yolu göster.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Peki, ne sorularınız var, efendim? Merakınızı gidermeye çalışacağım...";
			link.l1 = "Biliyor musunuz, mademoiselle - beni asıl ilgilendiren şey hanımınız, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Onun hakkında ne söyleyebilirim? O hâlâ bir muamma, bizim için bile. İyiliğimizi, sağlığımızı ve güvenliğimizi önemsese de, kimseyle samimi olmaz, aramıza katılmaz.";
			link.l1 = "Belki uzun sohbetleri sevmiyordur. Söylesene, aksanlı mı konuşuyor?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Hayır, bunu neden düşündünüz? Sırf teni sarı diye mi? O, tertemiz Fransızca ve birkaç başka dil konuşur. Ayrıca konuklarla ve potansiyel ortaklarla herhangi bir konuda saatlerce sohbet edebilir.";
			link.l1 = "Demek öyle. İlginç... Şimdi burada mı? Eğer öyleyse, hemen içeri girip onunla görüşeceğim ve sizin gerçekten... değerli vaktinizi daha fazla harcamayacağım, işinize dönebilirsiniz.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = " Geri dönecek pek bir şey yok - ama ev sahibemizin amacı burayı Tüm Takımadalar'ın en iyi yeri yapmak. Seçkin bir mekan; hiçbir tüccar, soylu ya da eğitimli biri buraya gelmekten utanmaz - çünkü biz bedenlerimizden fazlasını sunuyoruz.";
			link.l1 = "Ama bunda pek başarılı sayılmaz, değil mi?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Nasıl anlatsam... Bizi, sıradan yerlerde olduğu gibi sadece birer mal olarak değil, birer proje olarak görüyor. Pahalı giysiler, ilaçlar, eğitim - her birimize yatırım yapıyor. Eski Dünya'daki büyük bir şehirde olsak, kesinlikle başarılı olurdu! Ama burada... En yetenekli tüccar bile, mallar o kadar pahalıysa ve neredeyse kimse alamıyorsa, hiçbir şey kazanamaz. Fiyatları düşürsek bile, bir gün iflas etmeye mahkûmuz.";
			link.l1 = "Bunu duyduğuma üzüldüm. Peki, hanımınız şimdi nerede?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Burada şimdiye kadar iyi bir hayatımız var, bunu söyleyebilirim. Ama bunu hak etmek ve onun standartlarına ayak uydurmak da bir bedel gerektiriyor... Hanımefendiye gelince, o Hispaniola'ya gitti, hepimizi Port-au-Prince'e taşımak ihtimalini görüşmek için – sonuçta, orada daha fazla ticaret yolu kesişiyor ve ticaretimiz orada öylece durup neredeyse sürekli zarar görmeyecek.";
			link.l1 = "Öyle mi? Levasseur buranın istikrarı için yatırım yapmamış mıydı?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Çok fazla değil. Bize geldi ve dedi ki, ancak arada bir onun yerine gidersek büyük yatırım yapacakmış. Ama hanımefendi buna kesin bir şekilde karşı çıktı. Öyle ki, Ekselansları bir an afalladı. Onları daha önce hiç böyle görmemiştim.";
			link.l1 = "Heh-heh, şuna bak. Biliyor gibi... Cesur, çok cesur bir hareket bu.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Biliyor musun? Ama madem böyle güzel konuşuyoruz, sana başka bir şey daha söyleyeceğim, ama bu büyük bir sır, kimseyle konuşma sakın!";
			link.l1 = "Ah, hayır, mademoiselle. Size temin ederim, hanımefendinize hiçbir şekilde zarar vermek gibi bir niyetim yok. Lütfen devam edin.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Onu incitebileceğinden bile emin değilim, çünkü Belle Etoile her gün eskrim çalışıyor ve bütün şehirde ona denk bir rakip yok. Port-au-Prince'e ek olarak, Marcus Tyrex'in kendisine yatırım teklif etmeyi planlıyor! Ya da daha doğrusu, ondan borç almayı düşünüyor. Hayal edebiliyor musun?";
			link.l1 = "Evet, ve bugün düzenli olarak eskrim yapan başka bir hanımla çok zorlu bir konuşma yapacakmışım gibi hissediyorum... Neyse, paylaştığınız için teşekkürler, mademoiselle. İyi günler ve bol müşteriler dilerim.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Teşekkür ederim. Ama neden bu kadar acele ediyorsunuz? Ücreti tamamen ödediniz, hem de daha fazla konuşmadık bile. Ayrıca, sizde bir asalet var, monsieur. Evimize gelen nadir zenginlerden çok daha fazlası. Gerçekten birbirimizin yanında olmaya ne dersiniz?";
			link.l1 = "Biliyor musun... ne lanet olsun? Neden kendime yalan söyleyip istemiyormuşum gibi davranıyorum? Senin gibi bir kadınla bir şans çok nadir bulunur.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Ah, üzgünüm, hayır, mademoiselle. Sadece konuşmak için geldim. Ayrıca... beni bekleyen biri var.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Sanki bu birilerini durdurmuş gibi. O halde, saygıyı hak ediyorsunuz, monsieur. O 'biriniz' için çok sevindim.";
			link.l1 = "Tekrar teşekkür ederim, madam. Hoşça kalın.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Teşekkür ederim. Öncelikle birlikte sıcak bir banyo yapmaya ne dersin?";
			link.l1 = "İki el de kabulden yana.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Bu gerçekten büyülü bir deneyimdi, monsieur. Bir erkeğin beni böyle şaşırtabileceğini düşünmemiştim. Bir kadına nasıl zevk vereceğinizi biliyorsunuz...";
			link.l1 = "Kadına bağlı.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Pişman mısın?";
			link.l1 = "Şu anda, kesinlikle hayır. Hoşça kal, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Nereye gittiğine dikkat et, sahtekar!";
			link.l1 = "Ağzını topla!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Ben yoluma bakıyordum, sen ise kargaları sayıyordun.";
			link.l1 = "Etrafına bakmış olsaydın, dolaşabilirdin, değil mi?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Neden senin etrafından dolaşayım?!";
			link.l1 = "Şehir dışında, kimin kime ne borcu var, bunu öğrenelim derim.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, hayır. Efendim Kaptanım, bir erkeğin istemeden dokunuşundan bu kadar tiksineceğinizi bilmiyordum.";
			link.l1 = "Tekrar eder misiniz?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, üzgünüm. Seni zor durumda bırakmak istememiştim.";
			link.l1 = "Bu daha iyi.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Eğer yarım saat daha gecikseydin Charles, toplarımızı bu pis inin üstüne yağdırıyor olurdum, di mi! Aradığını buldun mu? O mu, Longway'in kardeşi? Onu gördün mü?";
			link.l1 = "Şşş, Mary, öyle konuşma. Hayır, Chang Xing ile tanışamadım...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "O zaman seni orada bu kadar uzun tutan neydi?! Ne halt ediyordun orada?";
			link.l1 = "Endişelenecek hiçbir şeyiniz yok. Elimden gelen her şeyi öğrendiğim anda, size söz verdiğim gibi oradan ayrıldım.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Sadece söyle gitsin, di mi!";
			link.l1 = "Sahibi şu anda Tortuga'da değil. Burada hizmetlerine olan talep düşük, çünkü yanında pahalı giysiler giyen iyi eğitimli hanımlar çalışıyor ve sadece altın kabul ediyorlar...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Onlara da mı para verdiniz?!";
			link.l1 = "Bana başka türlü konuşmazlardı bile. Böyle bir yaklaşımla, fazla müşterileri olmamasına şaşmamalı. Madame, daha zengin bir müşteri kitlesi çekmek umuduyla işini Port-au-Prince'e taşımaya karar verdi. Ama belli ki parası yok, çünkü borç almak için Marcus Tyrex'e gitmeye karar vermiş...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Onu tanıyor mu?";
			link.l1 = "La Vega'ya vardığımızda öğreneceğiz. Eğer acele edip gereksiz gevezelikle vakit kaybetmezsek, kim olursa olsun bu Asyalı kadını yakalayacağız.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "O geneleve gitmek gereksizdi, Charles. Eminim biraz daha uğraşsaydık, bütün bunları meyhanede ya da sokakta da öğrenebilirdik, di mi.";
			link.l1 = "Bir dahaki sefere seni de yanıma alacağım ki o güzel kızıl kafanı saçma şeylerle doldurmayasın, ha? Şimdi, asıl meseleye geçelim.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Ah, biraz geciktim galiba, di mi! Dur bakalım, seni alçak...";
			link.l1 = "Mary, burada ne işin var senin?! Sana teknede kal dedim!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Yani seni fahişelerle eğlenmekten alıkoymazdım, öyle mi?! Bunu inkâr etmeye bile kalkma, Charles! Mürettebat seni orada gördü, di mi! Nasıl yapabildin?!";
			link.l1 = "Ben de öyle düşünmüştüm. Sanırım onları yanıma alsaydım iyi olurdu, böylece ne yaptığımı - ya da aslında ne yapmadığımı - görürlerdi ve bu kadar büyütmezlerdi...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Bizim çocuklarımızı yalan söylemekle mi suçluyorsun? Senin yaptıklarından sonra, kaba herif?";
			link.l1 = "Onları sadece eşsiz bir aptallıkla suçluyorum. Durumu anlamadan, siz...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, senin ve fahişelerinin, o deliğe zamanında yetişseydim durumu nasıl anladığımı hiç beğenmeyeceğini düşünüyorum. Ama şanslısın - bu lanet kayığı tek başıma çekmek zorunda kaldım...";
			link.l1 = "Ağır bedensel işin insanın kafasını gereksiz düşüncelerden arındırdığı söylenir. Ama senin kafanda hâlâ bir sürü düşünce var, o yüzden sen de kürek çekiyorsun.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Kımıldamıyorum, di mi!";
			link.l1 = "Mary, bu konuşmayı Levasseur'un adamlarının önünde yapmayacağım. Sakin ol, etrafına bak ve bir karar ver. Burası ne zamanı ne de yeri.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Cehenneme kadar yolun var. Hâlâ kamarada eşyalarım var... Ama sakın bir daha kürek çekeceğimi sanma, tamam mı! İçinde biraz asalet kalmış olmalı!";
			link.l1 = "Ben bir alçak ve bir zorbayım, unutma. Bunu gemide kanıtlayacağım, ama önce oraya varmam gerek. Yani yalvarışların boşuna.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Bütün tayfa sana gülüyor, di mi!";
			link.l1 = "Eh, belki sana da bakıyorlardır. Uzun zamandır böyle bir gösteri görmemişlerdi. Şimdi öfken biraz dinmişken, sana olanları anlatayım.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, artık her şeyi duydum. Sadece bir sorum var: Sana yetemedim mi? Bende eksik olan ne var?";
			link.l1 = "Nezaketsizlik olacak ama ben de bir soruyla cevap vereceğim: Sana hiç güvenmemek için bir sebep verdim mi? Ha? Ben öyle bir şey hatırlamıyorum. O yüzden derin bir nefes al ve beni dinle. Joep van der Vink hakkında fazla bir şey öğrenemedim, sadece bir geneleve gittiğini bulabildim. 'Şarkı Söyleyen Karga'nın yanındaki değil, iskeleye yakın başka bir yere. Daha önce orayı bilmiyordum... ama belli ki bizim denizciler biliyormuş ve seni de haberdar etmişler. Gerçi oraya gitmelerine izin verilmezdi...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Denizcileri içeri almayan ne biçim genelev olur, di mi?";
			link.l1 = "İpekler içinde çalışan, kafalarında sadece hava olmayan kadınların bulunduğu bir genelev. Ve hizmetleri yalnızca altın dublonla ödeniyor. Bu herhangi birinin kaprisi değil, gizemli hanımları Belle Etoile'ın emri.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Gizemli, di mi?";
			link.l1 = "Sadece bu değil. O Asyalı.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asyalı mı? Tortuga'daki genelevin patroniçesi mi?";
			link.l1 = "Chang Xing olabilir. Bu yüzden oraya gittim - onu kendi gözlerimle görmek istedim. Hepsi bu.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Nasıl biri?";
			link.l1 = "Hiçbir fikrim yok. Orada değildi, bu yüzden başka bir... yıldızla sohbet etmek zorunda kaldım.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "O da Asyalı mıydı, di mi?";
			link.l1 = "Hayır, o beyazdı. Bana Belle Etoile'ın son zamanlarda pek iyi gitmediğini, bu yüzden Port-au-Prince'e taşınmaya karar verdiğini söyledi. Mantıklı, oradaki insanlar daha zengin olur. Madamın paraya ihtiyacı olmalı, çünkü Espanola'da bir ticaret açmak için borç alması gerekiyor, ki bunu Tyrex'ten almayı planlıyor. Yani eğer La Vega'ya acele edersek, Marcus onunla buluşmadan önce onu yakalayabiliriz.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Ne onun, ne Marcus'un, ne de başka birinin umurundayım, di mi. Charles, bana sadece bir şey söyle - onun genelevindeki kızlardan biriyle oldun mu?";
			link.l1 = "Buna ihtiyacım yok, Mary. Sen varsın, dünyanın en harika kızı. Neden bunu anlamadığını gerçekten bilmiyorum.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Aslında gerçeği anlamak çok kolay, di mi, hihi. Eğer kimseyle olmadıysan, şu anda enerjin tavan yapmış olmalı. Şimdi bunu kontrol edeceğiz, di mi!";
			link.l1 = "Mary, lütfen..";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					Notification_Perk(true, "Medic");
					dialog.text = "(Mükemmel Sağlık) Ugh... Görünen o ki yalan söylemiyormuşsun, Charles, tamam...";
					link.l1 = "Seni kandırmaya ihtiyacım yok, sevgili...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					Notification_Perk(false, "Medic");
					dialog.text = "Charles, sen... sen ciddi misin?! Bu da neydi?";
					link.l1 = "Ah, bu sıcak bana hiç iyi gelmiyor. Öhö.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Görünen o ki yalan söylemiyormuşsun, Charles, di mi...";
				link.l1 = "Seni kandırmaya ihtiyacım yok, sevgili...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Ama o sandal yolculuğunu uzun süre unutamayacağım!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Daha önce bundan hiç şikayet etmemiştin, değil mi?";
			link.l1 = "Şu lanet adada bir koşmayı dene de gör...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "Ve genelevler, di mi! Gerçekten...";
			link.l1 = "Mary, üzgünüm.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Ne?! Yani sen...";
			link.l1 = "Bunun için üzgün değilim. Kahretsin. Yani, senden başka kimseyle olmadım, sana söyledim. Sadece... içimi rahatlatamadım, hepsi bu. Bunu yapmak zor, biliyorsun, La Roche'un topları sana bakarken.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Bu güzel bir bahane, Charles. Peki, sana inanacağım. Bu sefer... Ama bil ki hâlâ sana kızgınım, tamam mı!";
			link.l1 = "Affınızı kazanacağım, söz veriyorum.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Pekala, sevgilim, bana ne öğrendiğini anlat. Benim gözüme girmek için riske girmeye değdi mi?";
			link.l1 = "Gerçekten şaka mı yapıyorsunuz yoksa ciddisiniz anlamak zor. İşe yaradı – ev sahibini kendi gözlerimle görmesem de. Kendisi Asyalı ve adı Belle Etoile – harika bir yıldız. Tabii ki gerçek adı değil...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "Ve bunun için geneleve mi gitmen gerekiyordu? Hanede bunu öğrenemez miydin?";
			link.l1 = "Kasabada buradan pek bahsetmiyorlar. Neden? Güzel soru. Bunu bizzat Belle Etoile'a sorabilirsin - o şimdi Espanola'ya gitti.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Tortuga ona yetmedi mi?";
			link.l1 = "Burada ticaret, anlaşılan, pek iyi gitmiyor. Liman kızları yerine zengin giyimli, eğitimli hanımlar çalıştırıyor.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "Ve bunu neden yapsınlar ki?";
			link.l1 = "Bu da güzel bir soru. Her neyse, bizim küçük kuş Port-au-Prince'e, de Mussac'ın hükümranlığına uçmaya karar verdi. Ama bu girişim için gereken borç, bizzat Tyrex'ten alınacaktı.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Bu hikayenin bir an önce bitmesini istiyorum. Hiç vakit kaybetmeden La Vega'ya doğru yelken açalım.";
			link.l1 = "Böyle yapacağız.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Cesur bir adamsın Charles, bunu kabul etmeliyim. Hiçbir şey olmamış gibi, böyle rahatça ve yüzünde en ufak bir ifade değişikliği olmadan ortaya çıkıyorsun.";
			link.l1 = "Sanırım tayfalardan biri gevezelik etti? Tabii ki hiçbir açıklama yapmadan. Çünkü aslında hiçbir şey olmadı—en azından düşündüğün gibi değil.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Bunu inkar etmediğine sevindim, Charles.";
			link.l1 = "Sana her şeyi anlatacaktım, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Yapma, Charles. Ayrıntılar pek ilgimi çekmiyor. Ama nedenler önemli. Söylesene, bende bir tuhaflık mı var?";
			link.l1 = "Nedenlerden başlayalım. Tortuga'da iki genelev olduğunu öğrendim. Biri herkesçe biliniyor. Diğeri ise... insanlar varlığını biliyor ama pek konuşmak istemiyor. Sahibi Asyalı bir kadın...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Bunu kafandan mı uyduruyorsun?";
			link.l1 = "Neden böyle bir şey yapayım ki, Helen?! Bana inanmıyorsan, oradakiler de doğrulayacak!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Öncelikle, karaya çıkmamamı söylediniz, yani oraya gitmemin imkânı yok. İkincisi, beni kim sanıyorsunuz siz?! Öyle bir yere asla yaklaşmam! Üçüncüsü... devam edin işte.";
			link.l1 = "Güzel. Oraya gitmeye karar verdim, Madame Étoile'ü kendi gözlerimle görmek için. Tek niyetim buydu, kahretsin!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Sanırım. Onunla tanıştınız mı?";
			link.l1 = "Hayır. O, Espanola'ya gitti. Burada işleri iyi gitmiyordu, bu yüzden şansını Port-au-Prince'te denemeye karar verdi. Orada, onun yanında çalışan ipekler içinde, iyi eğitimli hanımlar ona Tortuga'dan daha fazla kazanç getirebilir...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Giyimli kuşamlı ve eğitimli mi? Vay be, hayat insana neler getiriyor. Ama onları oldukları gibi sevmelisin.";
			link.l1 = "Helen, yapma. Güvensizliğini hak edecek bir şey yapmadım.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Doğru. Beni kandırmaya kalksaydın, bu kadar sakin olmazdın. Ama planlarından beni haberdar etmeliydin, Charles.";
			link.l1 = "Haklısın, canım. Ama biraz zaman kazanmak istedim. Hata ettim.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Pekala. Şimdi ne yapıyoruz, Port-au-Prince'e doğru rota mı çiziyoruz?";
			link.l1 = "La Vega. Şaşırma, Helen. Madame Belle Etoile iyi durumda değil. Ticaretini Port-au-Prince'e taşımak için borca ihtiyacı vardı, bu yüzden Marcus'tan borç almaya karar verdi. Eğer acele edersek, onu orada yakalayabiliriz. O yüzden bir dakika bile kaybetmeyelim.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ_1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ_1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Mary();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				ReturnOfficer_Helena();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Sizin gibi bir serseri ve sürünüzün bizi yendiğine inanamıyorum!";
			link.l1 = "Sen...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Beni tanıdınız mı?";
			link.l1 = "Tanışmış mıydık?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Ne?! Benimle dalga mı geçiyorsun lan?!";
			link.l1 = "Karşılaştığım bütün vahşi pislikleri hatırlayamam. Bize seni kim gönderdi, anlat bakalım. Yoksa senden kurtulmak mı istediler?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Senin gibi birine hiçbir şey söylemeyeceğim. Kendini ne kadar da büyük görüyorsun! Bakalım, burada biraz soluklandıktan sonra da aynı şekilde konuşabilecek misin?";
			link.l1 = "Ne yazık. İğrençsin, ama seni başka bir adaya bırakabilirdim. Şimdi yapabileceğim tek şey seni öte tarafa göndermek.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Beni mi çağırdınız, Kaptan?";
			link.l1 = "Evet, dostum. Hasarı bildir.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Evet, fark ettim. Tichingitu, dostum. Ben ve "+sStr+" Karaya çıkacağım. Sen burada kal ve idareyi üstlen. Hemen tamirlere başla - fırtına dinene kadar tersaneye gitmenin anlamı yok. Hem, burada uzun süre kalmayacağız.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Her şeyi daha güzel göstereceğim.";
			link.l1 = "Harika, teşekkürler. O zaman hiçbir endişemiz olmadan şehre gidiyoruz.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Efendim Kaptanım? Bir onur bu. Ama genelde böyle zamanlarda Alonso'ya seslenirsiniz. Bir sorun mu var, sorabilir miyim?";
			link.l1 = "Evet, her şey yolunda. Ama bizim Alonso daha çok yıkım konusunda iyidir, bir şeyi tamir etmekte değil. Her anlamda. Gemi ne durumda?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso sana berbat olduğunu söylerdi, aşağı inmeyecek olsak bile. Tamirlerden bahsettin - başlayalım mı?";
			link.l1 = "Evet, elinden geleni yap. Ama uzun vadeli, kapsamlı bir işe kalkışma – işimi şehirde bitirir bitirmez demir alacağız. Ben ve "+sStr+" orada olmayacağım, bu yüzden herhangi bir durumda tüm kararları kendin ver. Her konuda Alonso'yu dinle.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Emriniz olur, Monsieur le Capitaine.";
			link.l1 = "Rahat ol.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Selamlar, monsieur! Port-au-Prince'e hoş geldiniz.";
			link.l1 = "Ve size de iyi günler, monsieur. Siz kimsiniz ve bu karşılamayı neye borçluyum? Bu yağmurda ve fırtınadan sonra uzun bir sohbete pek hevesli olduğumu söyleyemem.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Ah, vaktinizi fazla almayacağım, Monsieur de Maure.";
			link.l1 = "Sizi tanıyor muyum?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Ah, hayır, ama tüm takımada sizin kim olduğunuzu biliyor. Ah, görgüsüzlük ettim! Henri Thibaut, hizmetinizdeyim. Ben, Efendimiz Monsieur de Mussac'ın habercisiyim. Geminizi görür görmez bana sizi en sıcak şekilde karşılamamı emretti, monsieur.";
			link.l1 = "Pekala, bu çok şeyi açıklıyor. Tanıştığımıza memnun oldum, Mösyö Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "Ve memnuniyet karşılıklı, Monsieur de Maure! Lütfen beni takip edin. Sizin gibi saygın bir beyefendi ve güzel refakatçinizin bu pis meyhanede kalması hiç uygun olmaz. Lordunuz şehirde size bir ev tahsis etti ve bana da her konuda size yardımcı olmamı emretti. Lütfen sonrasında Ekselansları Poincy'ye en iyi dileklerini iletmeyi unutmayın.";
			link.l1 = "Aslında, işim biraz gizli. Biliyor musunuz, Monsieur Thibaut, sanırım...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Sana nadiren bir şey rica ederim, hele ki sözünü kesmem pek olmaz, ama onların teklifinden yararlanabilir miyiz? Yağmurda ıslanmaktan bıktım. Ayrıca midem bulanıyor ve başım dönüyor.";
			link.l1 = "Heh-heh, gerçekten yağmur olduğuna emin misin?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Dilini tut, Charles! Her neyse, dinlenmek istiyorum. Büyük bir yatakta ve dalgasız.";
			link.l1 = "Pekala. Kurulanırız, biraz dinleniriz, sonra da işe kaldığımız yerden devam ederiz.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Bu evde biraz dinlenebilir miyiz? Kendimi iyi hissetmiyorum, bir de... yorgunum Charles. Di mi?";
			link.l1 = "Mary, canım, anlıyorum ama belki meyhaneye gitmeliyiz. Bütün bu işin kokusu kötü geliyor, değil mi?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Bana ne olabilir ki? Burası Tortuga bile değil.";
			link.l1 = "İşte bu beni korkutuyor.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Lütfen? Eğer bir şey olursa, odada savunmamı kurarım-tıpkı... o zamanlar gibi, tamam mı. Beni herkesten iyi tanırsın Charles, bu yüzden bunun üstesinden gelebileceğimi biliyorsun.";
			link.l1 = "Pekala, pekala. Umarım bu sefer o zamanki gibi olmaz.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Fikrinizin değişeceğini biliyordum, monsieur! Endişelerinizi tamamen anlıyorum. Fakat bakın, Ekselansları Poincy ile valimiz eski dostlardır, bu yüzden kasabamızda hoş karşılanan bir misafirsiniz, Monsieur de Maure!";
			link.l1 = "Ah, peki... O zaman, bizi o eve götür o zaman.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Elbette, monsieur! Lütfen beni takip edin.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Efendim, vali sizi bekliyor. Sizi en kısa sürede yanına çağırdı - sizinle özel olarak konuşmak istiyor.";
			link.l1 = "Bunu zaten biliyor mu?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Elbette biliyor! Bu yüzden seni bekliyor. Sevgilin tatlı uykusunda kalsın, sen de monsieur de Mussac'ı görmeye git. Bir fırtına ünlü Charles de Maure'u durduramaz, değil mi? Ama Efendimiz, gördüğün gibi, randevuları arasında fazla vakit ayıramıyor...";
			link.l1 = "Doğru, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Sana yolu göstereceğiz, Kaptan.";
			link.l1 = "Demek bana bir de fahri refakatçi verdiniz... Peki öyleyse, buyurun önden gidin.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Efendim Kaptanım!";
			link.l1 = "Longway! Gemiye! Şimdi!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Ama Chang Xing'i gördüm!";
			link.l1 = "Ne?! Nerede? Ne zaman? Geminizde mi o?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Hayır! Şehirde, Longway onu uzaktan gördü. Yetişmeye vakit yok - yeni demir alan bir kalyona biniyor!";
			link.l1 = "Galyonu yakalayacağız! Ama söyle bana - gördün mü "+sStr+" herhangi bir yerde mi?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Hayır! Bir şey mi oldu?";
			link.l1 = "Evet, bir şey oldu! O tehlikede! Levasseur'un yeğenini gördünüz mü? Adı Henri Thibaut! Kötü, sıska, uzun saçlı, komik bıyıklı bir genç!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(Mandarince) Komik bıyıklardan bahsetmenize gerek yok, Kaptan... (kırık Fransızca ile) Onu gördüm! O ve paralı askerler de aynı kalyona bindiler.";
			link.l1 = "Hemen peşine düşelim!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Gemiciniz çok kötü durumda, Efendim Kaptanım!";
			link.l1 = "Umurumda değil! "+sStr+"Hayatı tehlikede!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Benim... 'Senin Meifeng'in' bizi buradan çıkaracak!";
				link.l1 = "Ah, edecek! Acele et!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Bizi intihar saldırısına sürüklemeyin. Daha önce bana verdiğiniz gemiyi kullanın!";
				link.l1 = "İyi fikir, Longway! Hadi acele edelim!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			AddDialogExitQuestFunction("PZ_Longway_78");
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Yine sen... Biliyordum, reddetmeliydim ve başka birine senin kızını bırakmalıydım.";
			link.l1 = "Nerede o?! Söyle bana! Hayır... Kapa çeneni. Sadece ambarın dibinde, zincirlenmiş halde konuşacaksın! Duydun mu?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "Kılıcı. Eğer hemen şarkı söylemeye başlamazsan, seni onunla parça parça ederim.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Sen... sen aklını tamamen yitirmişsin!..";
			link.l1 = "Şimdi işin kötü tarafımı göreceksiniz...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Hepsi bu mu?";
			link.l1 = "Bir kez daha soruyorum! Nerede "+sStr+"?! Çinli kadın nerede?! Henri Thibaut nerede?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(kan tükürür) Bir kızı gibi vuruyorsun.";
			link.l1 = "Seni kahpe! Her kelimeyi döve döve alacağım senden!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Acınası. Gerçi... Söyleyeceğim. Neden olmasın, ha ha. Hepsi diğer gemide, tam Tortuga'ya giden yolda. Çok geç kaldın.";
			link.l1 = "Eğer başındaki bir tel saçına bile zarar gelirse...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "Ve bunun suçu kimde?! Edgardo Sotta’yı sen öldürdün! Levasseur hayatında ilk kez bir kızı arzuladı ve hemen elde edemedi! Mürettebatımız ilk defa onun doğrudan emrini yerine getiremedi! O adam şeytan kadar korkutucu olabilir...";
			link.l1 = "O zaman şeytanın kendisinden bile daha korkunç olurum ve bana bilmek istediğimi söylemezsen sana kendi cehennemini yaşatırım, beni duyuyor musun?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Senin dertlerin umurumda değil - zaten ölü bir adamım ben, şu delirmiş gözlerine bakılırsa. Yine de sana biraz hakkını vereceğim, de Maure.";
			link.l1 = "Ne saçmalıyorsun sen?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur sarışınları sever. Ama ben her zaman kızılları daha çok sevdim, tıpkı senin gibi, hehehe... Ne ateşli birini bulmuşsun!";
			link.l1 = "Haklısın, bu günü çıkaramayacaksın...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Ne istediğin umurumda bile değil. Ama sana söyleyeyim  Levasseur ne ister - güzel sarışın kızlar, ha ha ha ha ha ha ha ha ha! Önce, onu aldı...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Silahsız bir adamı dövüp çığlık atmak – acınası. Yapabildiğin tek şey bu. Kaybettin, de Maure! Gerçekten ne zaman kaybettiğini bilmek ister misin, zavallı ahmak?";
			link.l1 = "Beni aydınlat. Ama etkilenmezsem, bir parmağını kaybedersin. Ya da bir kulağını. Ya da o çürük dişlerini, o pis ağzından. Belki de başka bir şeyini. Seçim senin...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, sende olmayan bir şeyim var. Levasseur’un, o kurnaz tilki Poincy’nin ona karşı ne planladığını bilmediğini mi sandın? François her şeyi bilir, her şeyi! Kardeşlik baronları bile ona meydan okumaya cesaret edemez. Ama sen, akıllı geçinen, sen ettin. Ama...";
			link.l1 = "Ama ne?! Sakın ha, bu işi uzatmaya kalkma!! Konuşmaya başla, yoksa parmaklarını teker teker kırmaya başlarım!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, cesur Kaptan de Maure! Ama peki. Ben, Henri ve o sarı tenli kadın, seni burada yok etmenin en iyisi olacağına karar verdik. Sonra da suçu Tyrex'in üstüne atarız, böylece Kardeşlik'teki yaşlı ahmaklar yine birbirleriyle savaşa başlar! Ya da belki de Mussac'a - burnunu gereksiz yere her şeye sokuyor... Biliyor musun, herkes bana kalyonla denize açıldığım için güldü, ama fırtınayı kolayca atlattı, senin o paçavra teknen gibi değil.";
			link.l1 = "Yeter! Levasseur kurbanlarını nerede tutuyor?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Demek onun gizli yerini, zindanı biliyorsun? Evet, o gerçek bir zindan efendisi, ha-ha-ha! Ama gerçekten ona meydan okuyabilir misin? Sanmam. Canavarı yenmek mi istiyorsun? O zaman önce kendin canavar ol. Bakalım, beni Francois'nın o kızları kırdığı gibi kırabilecek misin. Tıpkı yakında seninkini de kıracağı gibi...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Sana karışma dedim, kahretsin!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "İzin verin, Efendim Kaptanım.";
			link.l1 = "Longway? Ne demek bu, izin vermek?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Beyaz adamlar bedeni işkence eder. Benim halkım bilir ki, önce zavallı bir ruhu işkence etmek gerekir, sürekli küçük bir acıyla delirtmek. Hazırlık olmadan alıp işkence edemezsin. Her zaman özel bir yaklaşım gerekir. Burada ise... Lynchy lazım.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Evet, Efendim Kaptanım. Bin kesikle ölüm.";
			link.l1 = "Sen deli misin?! Kafanı mı kırdın? Hangi ölümden saçmalıyorsun?! Önce onu konuşturmalıyım!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway biliyor, Efendim Kaptanım. Ne yapacağını biliyor. Bu alçak bana her şeyi anlatacak. Bana biraz zaman verin...";
			link.l1 = "Zaman mı? Zaman mı?! Peki... Yapın. Sadece lütfen, yalvarıyorum, ondan her şeyi alın, her şeyi!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_LongwayKazn_3_1", -1);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Beni öldür, sadece öldür, lütfen... Daha ne istiyorsun benden?!";
			link.l1 = "Daha fazla konuşma. Çeneni kapa ve geber.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Temiz atıştı, Efendim Kaptanım. Söylemiştim işe yarayacak diye.";
			link.l1 = "Evet. İyi iş çıkardın. O zaman zindana gidiyoruz. Tüm yelkenleri açın! Rotayı Tortuga’ya çevirin. Ve eğer kız kardeşimin saçının teline zarar gelirse, Tanrı bu lanet şehre yardım etsin. "+sStr+" kafa...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			AddQuestRecord("PZ", "39");
			pchar.questTemp.PZ_FlagMartinInfo = true;
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Sizi hiç böyle görmemiş ya da duymamıştım, senyor Kaptan.";
			link.l1 = "Tamamen senin, Alonso! Hadi bakalım, bana Kutsal Engizisyon'un Huguenotlara ve onların uşaklarına neler yaptığını göster... Ve ben izleyeceğim... Sonra onunla ne istersen yapabilirsin.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Aye aye, senyor Kaptan...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Uzun sürmez, senyor Kaptan...";
			link.l1 = "Yap şunu, Allah aşkına!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Kalk, seni pislik. Kalk dedim sana!";
			link.l1 = "Öldü mü? Öldü mü gerçekten?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Öyle görünüyor, kaptan...";
			link.l1 = "Ne halt ettin sen?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Kim bilebilirdi bu ahmağın bu kadar zavallı çıkacağını! Altına da yapmış, pislik herif! Lanet olsun, ateş gereksizmiş...";
			link.l1 = "Sen... Onu balıklara atın. Rotayı Tortuga'ya çevirin. Gerekirse, o yeri taş taş sökeceğim – önce La Roche, sonra... Sonra, eğer onu sağ bulamazsam Tanrı yardımcım olsun...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			AddQuestRecord("PZ", "38");
			AddDialogExitQuestFunction("PZ_FinalKaznOnShip_DlgExit");
		break;
		
		case "PZ_Norman1":
			dialog.text = "Sonunda. Bu taht artık benim. Bu kayanın üstünde inşa edeceğim...";
			link.l1 = "Ne oluyor... Cidden mi?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "...   kilisem.   Artık Roma'nın Papasıyım.   Tanrı'nın evinde küfretmeyin!";
			link.l1 = "Ve ben de sanmıştım ki... Peki, Aziz Efendimiz, sadık kullarınıza lütfeder de nerede olduğunu söyler misiniz "+sTemp+" şimdi mi?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Kutsal bir göreve çıktı. Yeni bir haçlı seferi, isterseniz öyle deyin. Kötülerden parayı alıp bana getirecek.";
			link.l1 = "Sana, doğru. Ne zaman döneceğini söyledi mi?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Bir ay içinde. Belki biraz daha geç. Onun dönüşünü bekliyorum, sürümüzün geri kalanıyla birlikte.";
			link.l1 = "Demek gerçekten denizdeymiş. Sende ne varsa bana da bulaşmadan gitsem iyi olacak.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Hepsini kutsal alevlerde arındıracağım...";
			link.l1 = "Kafanın biraz temizlenmeye ihtiyacı var...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! Size nasıl yardımcı olabilirim?";
					link.l1 = "Merhaba, Helen! Seninle konuşmak istiyorum "+sTemp+" . Yukarıda mı? Yoksa meyhanede mi?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! Ve... Ah, ne hoş bir sürpriz. Size nasıl yardımcı olabilirim?";
					link.l1 = "Merhaba, Helen. Nerede "+sTemp+"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. Seni buraya ne getirdi?";
				link.l1 = TimeGreeting()+", Helen.   Ben arıyorum  "+sTemp+" . Onun nerede olduğunu biliyor musun?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Dışarıda, ama ne yazık ki uzun süre yok - denizde, daha doğrusu.";
			link.l1 = "Lanet olsun. Bir şey mi oldu? Ne zaman döneceğini söyledi mi?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Hayır, ama önemli bir şey değil - her zamanki gibi iyi bir iz bulmuş. Genelde bir ayda, en fazla iki ayda döner. Nasıl olduğunu biliyorum, bazen ben de geminin güvertesini özlüyorum...";
			link.l1 = "Her zaman denize açılabilirsin. Bir gün birlikte gitmek güzel olurdu - sen 'Gökkuşağı'nda, ben de...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Olurdu. Ama senin... sevgilin bundan hoşlanmayabilir. Ve ben de aranıza üçüncü kişi olmak istemem.";
			link.l1 = "Öhö, pardon Helen, seni kırmak istememiştim. Sohbet için teşekkürler. Sonra görüşürüz.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, geri döndün. Sana başka nasıl yardımcı olabilirim?";
			link.l1 = "Hayır, teşekkür ederim, Helen. Sadece kontrol etmek istedim, acaba "+sTemp+" ortaya çıktı.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Beni aramaya geldiyseniz şaşırırım. Peki "+sTemp+", denizde.";
			link.l1 = "Gerçekten mi? Ne zaman döneceğini söyledi mi?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Görünüşe göre bu bataklığı yönetmekten bıkmış ve hâlâ bir geminin kaptanı olduğunu kendine hatırlatmak zorunda kalıyor. İlk defa olmuyor bu. Genelde bir ayda, bazen bir buçuk ayda döner.";
			link.l1 = "Lanet olsun, demek baronlar her zaman öyle oturmuyorlar? Teşekkür ederim, Helen. Hoşça kal.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+"Hâlâ dönmedi, Charles";
			link.l1 = "Anladım, sadece kontrol ediyorum.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "O özgür bir adam, değil mi? İstediği zaman denize açılabilir.";
			link.l1 = "Elbette yapabilir. Peki, nerede şimdi?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Ama Charles, eğer adada değilse, o zaman İspanyolları yağmalamaya gitmiştir. Ve şimdi, izninizle, yapacak çok işim var. Ara sıra uğra - genellikle, "+sTemp+" yaklaşık bir ay sonra döner, bazen biraz daha geç.";
			link.l1 = "İyiyim, Helen, teşekkür ederim. Meşgul olacağız.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Şu anda havamda değilim. Belki başka bir zaman gelirsin, Charles?";
			link.l1 = "Tabii Helen. Rahatsız ettiğim için üzgünüm. Kendine iyi bak.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Yerimizi aldık, Efendim Kaptanım. Yolu hatırlıyor musunuz?";
				link.l1 = "Elbette, Longway. Yeter ki o lanetli zindanda onu kaybetmeyelim...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Yerimizi aldık, Efendim Kaptanım. Bir planınız var mı?";
				link.l1 = "Hâlâ üzerinde çalışıyorum... Neden sordun, aklında bir şey mi var?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Pekâlâ, sanırım Chang Xing'e aceleyle gidersek...";
			link.l1 = "Longway... Kız kardeşini görmek için ne kadar çok istediğini anlıyorum, ama "+sStr+" şu anda ölümcül bir tehlikede, ve bu sadece bir deyim değil! Onu kurtarmak birinci önceliğiniz olmalı, bunu anlamalısınız!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Efendim Kaptanım, bu on yıl boyunca neler yaşadığımı gerçekten anladığınızdan şüpheliyim. Şu anda neler yaşadığımı da.";
			link.l1 = "Biliyor musun, bir bakıma evet. Kardeşim hapiste tutuluyor. Ve ona henüz zarar vermediler ama her an ona istedikleri her şeyi yapabilirler.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ama sadece hanımefendi olsaydı nereye giderdiniz "+sStr+"   kurtarılmaya ihtiyacı olan kimdi?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Bir yer var... bir kişi... Ama bununla kendini yorma, Longway - bununla kendim ilgilenmeliyim.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "Aslında, nereye gideceğimi bile bilmiyorum. Her yerde dikkatsizce dolaşırsam, dikkat çekerim, ve sonra "+sStr+" kesinlikle bitti. Yani... Bilmiyorum.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Ne? Neden?";
			link.l1 = "Oraya seni öylece almazlar - orası yüksek sosyete, kahretsin. O yüzden, ben tek başıma gideceğim. Bu arada, sen de kız kardeşine git. Elimden geldiğince çabuk sana katılırım. İyi şanslar, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Sağ olun, Efendim Kaptanım. Size de bol şans!";
			link.l1 = "Ah, teşekkür ederim - bugün buna gerçekten çok ihtiyacım var. Hepimizin var.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Efendim Kaptanım...";
			link.l1 = "Boşver. Hadi gidelim, Longway, kız kardeşine. Şimdi ayrılırsak, ölürüz. Kız kardeşine acele edelim ve Levasseur'un ininin nerede olduğunu öğrenelim. Sonra yine birlikte gideriz – şu anda yardıma ihtiyacım var. Umarım çok geç kalmamışızdır.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Geç kalmayacağız, Efendim Kaptanım. Daha fazla oyalanmayalım ya da tartışarak vakit kaybetmeyelim. Hadi Chang Xing'e gidelim!";
			link.l1 = "Haklısınız, acele edelim.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Sen nereye gidiyorsun böyle? O kapının nereye açıldığını biliyor musun?";
			link.l1 = "Çok iyi biliyorum. Oraya işim için gidiyorum, meraktan ya da çalmak için değil.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Ne işi var? Madame Levasseur şu anda müsait değil. Hem, kendisi evli bir kadın - etrafta onun evinde dolaşmak doğru olmaz.";
			link.l1 = "Evli, di mi? Ama arada sırada davetler veriyor, değil mi? Özel olanlar da dahil. İşte bu da onlardan biri. Beni bekliyor, hem de acelem var.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Böyle bir şey olsaydı, beni mutlaka uyarırdı.";
			link.l1 = "Ben özel bir misafirim – anonslara ihtiyacı olmayan türden.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Evet, öyle bir misafir ki, Lordum beni vurdurur. Ya da Hanımefendi bizzat derimi yüzer.";
			link.l1 = "Daha önce Madame Marceline’in misafiri olmuştum. Emin ol, bundan sonra sana hiçbir şey olmayacak, asker.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Elbette, kör kalıp herkesi içeri almak - bu da şehir muhafızlarının işi.";
			link.l1 = "Bu işlere ayıracak vaktim yok, inatçı eşek...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Sen...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Ah evet, hanımefendi. Şövalyeniz sizi tekrar gördüğüne memnun oldu. Beni gördüğünüze şaşırdınız sanırım. Bu buluşmanın sevinci... karşılıklı değil mi?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Evet, yaptım. Belki bu adadaki en yakışıklı ya da en değerli adam olmayabilirim, bunu son görüşmemizde de söylemiştiniz, ama en azından dürüst bir adam olduğumu biliyorsunuz. Lütfen beni dinleyin hanımefendi - fazla vaktinizi... kıymetli zamanınızı almayacağım.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Tanrı aşkına susun, hanımefendi, bu çığlıkları kesin artık. Buraya sizi şövalyenizi kandırıp ejderhanın hazinesini çaldığınız için intikam almaya gelmedim. Ve emin olun, sizi öldürmek isteseydim, doğrudan vurur, sonra da canımı kurtarmak için kaçardım. Sonuçta burası Tortuga! Ama sanırım bunun bana yakışmayacağını siz de biliyorsunuz.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Ah, hayır! Sadece düşündüm ki... Neyse, önemli değil! Bakın, kötü niyetli insanlar hakkımda çirkin dedikodular yayıyorlar - zavallı bir kadıncağızım, istemiş olsam bile kimseye zarar veremem, kendimi de düşmanlara karşı savunamam. Üstelik, üzerinden o kadar zaman geçti ki... Bana kötü niyetle geldiğinizi sandım, iyi niyetle değil. Yanılmış olmama sevindim. Kötü niyetli insanlarla çevrili yaşamak çok zor.";
			link.l1 = "Nasıl inanabilirdim ki? Böyle bir şey duysam bile, tek bir kelimesine bile inanmazdım. Ama haklısınız - buraya sadece sizi görmek için gelmedim. Yine de geldiğime memnunum. Biliyorum, bu tuhaf gelecek ama... bu sefer şövalyenizin sizin yardımınıza ihtiyacı var, hanımefendi.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "Ve düşündüğümden çok daha hassassınız. Yine de hatasız değilsiniz, Monsieur de Maure - sizi daha... zarif beklerdim. Aslında... ya hep böyleydiniz, ya da Takımadalar sizi çoktan yozlaştırdı. Bir hanımla nasıl konuşulacağını yeniden öğrenmelisiniz. Ama haklısınız - dürüst bir adamsınız, gerçi... biraz basit.";
			link.l1 = "Ve siz gururlu ve kinci bir kadınsınız. Gözleriniz, sözleriniz ve... davranışlarınız bunu açıkça gösteriyor. Bu yüzden beni anlayacak biri varsa, o da sizsiniz. Tıpkı bir zamanlar sizi anladığım gibi. O halde geçmişte daha fazla oyalanmayalım. Bana yardım edebilir misiniz, hanımefendi?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... O zamanlar sana karşı kaba davrandığımı kabul ediyorum. Ama sadece sana tamamen güvenemediğim içindi, başka bir sebebi yok! Tüm elmasları benden alır mıydın? Yoksa hizmetçilerimizden öğrendiğini söyleyip kocamı oraya getirip, ondan çaldığımı iddia edip kendi payını inkâr mı ederdin? Sonuçta herkes onun gözüne girmeye çalışıyor, benim gibi zavallı bir kadının değil... Şimdi anlıyorum ki, senin hakkında yanılmışım. Lütfen özrümü kabul et... benim şövalyem.";
			link.l1 = "Şimdi onların samimi olup olmadıklarını bilmiyorum. Ama bunun önemi yok. Yardımınıza ihtiyacım var, Madame Marceline. Bu bir ölüm kalım meselesi. Lütfen reddetmeyin.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Yardımım mı...? Şehirdeki son kadın olmadığım kesin, ama sandığınız kadar büyük bir etkim yok. Ben hükmeden bir kraliçeyim, yöneten değil. Ama sizi dinleyeceğim. Mütevazı şahsiyetim sizin için ne yapabilir?";
			link.l1 = "Bunun sizin için hoş bir konu olmadığını biliyorum, hanımefendi, ancak eşinizi arıyorum ve mümkün olan en kısa sürede bulmam gerek. Gerçek şu ki...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Bu bir şaka mı? Şu anda konakta değil mi? O zaman işi için gitmiştir. Size yardımcı olamam, Monsieur de Maure.";
			link.l1 = "Gözlerini kaçırdın. Biliyorsun. Ben de biliyorum. Sadece oraya gitmem gerek. Lütfen zindanı ilk kez duyuyormuş gibi yapma - bunu bilmeyecek kadar saf değilsin.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Ah, bu konuşmanın başıma bir beyaz saç daha ekleyeceğini hissediyorum. Sanki ilk kırışıklıklarım yetmiyormuş gibi. Ne yapıyorsun bize böyle, Francois...";
			link.l1 = "Bir tutam gri saç sadece asaletinize asalet katar, güzelliğinizden hiçbir şey eksiltmez. Ama iyi, masum bir kız kocanızın eline düştü. Şimdi ise güzelliğini, sağlığını, hatta hayatını kaybetme riskiyle karşı karşıya!... Oraya düşenlerin başına neler geldiğini biliyorsunuz. Lütfen, hanımefendi. Marceline... Şövalyenize yardım edin.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Artık benim şövalyem değilsin, değil mi? Hadi ama, aptal değilim. Ama... sana yardım edeceğim, de Maure. Sonuçta, bu sonsuza dek süremezdi. Bir gün herkesin haberi olacaktı. Şimdi benim için önemli olan, zamanında ve doğru şekilde çıkmak. Ve... seni, ‘kocam’ın senin... tanıdığına yapacaklarının yol açacağı sonsuz acıya mahkûm edemem.";
			link.l1 = "Artık sizin şövalyeniz olmayabilirim, hanımefendi. Ama siz de başından beri benim hanımefendim olmadınız. Yine de, hayatım boyunca size minnettar olacağım. Peki, burası neresi?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Pekâlâ, sana inanıyorum Charles. Şehir zindanlarında. Kör bir çıkmazda büyük bir fıçı var, yanında da bu canavarın inine giden bir geçit başlıyor. İçeri bakmadım. Sadece bir kez, çok uzun zaman önce onu takip ettim. Ve o zavallı yaratıkların insanlık dışı çığlıklarını duyduğumda korktum.";
			link.l1 = "Bugün birçok hayat kurtardınız, hanımefendi. Sadece benim sevdiceğimi değil, gelecekte kocanızın eline düşebilecek herkesi de. Size minnettarım.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, bırakın bu boş sözleri, monsieur. Benden çok şey istediniz. Ve büyük bir risk aldım. Şimdi, yeni görevinizde ejderhanın inine başarıyla girin... benim şövalyem.";
			link.l1 = "Elimden geleni yapacağım. Hoşça kal, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Biz haydut değiliz. Ama bu kız onlarla boy ölçüşebilecek biri. Kılıcı süs olsun diye taşımıyor. Sadece yaralı. Bu adam benim dostum, aynı zamanda hanımınızın da kardeşi. O yüzden, bırakın onu görelim.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Sizi tekrar görmek güzel, monsieur! Ama biliyorsunuz, burada düşük sınıftan misafirleri kabul etmiyoruz. Tavsiye edilmiş ve parası ödenmiş olsalar bile. Hele hele sarı tenli işçiler ya da zenci köleler hiç olmaz. Korkarım arkadaşınız dışarıda kalmak zorunda.";
				link.l1 = "Bunu hanımefendinizin yanında söylemeyin. Onun da teni sarı. Ayrıca bu bir işçi değil, onun kardeşi. Bir aile buluşmasına engel olmazsınız, değil mi?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "Bu kızı kurtardım, ve bir daha asla kendine yakışmayan bir yerde çalışmayacak . Bir işçi mi diyorsun?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Ah monsieur, ne kötü bir zamanlama! Bugün artık misafir kabul etmiyoruz - burada neler olduğunu kendiniz görebilirsiniz.";
				link.l1 = "Bu yüzden buradayım. Bütün bunları organize eden sarı tenli bir adamdı, değil mi?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Evet, efendim, bir işçiydi! Ne dediğini zar zor anladık! Bu serseri içeri daldı ve hanımefendiyi görmek istediğini söyledi. Onun kardeşi olduğunu iddia etti. Adamları çağırdık ama...";
			link.l1 = "Bu onun için bir engel değil. Sonra ne oldu?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Meğerse yalan söylemiyormuş. Kadın yanımıza çıktı ve onu tanıdı. Hatta hâlâ onun lüks yerinde konuşuyorlar.";
			link.l1 = "Kim bilir onun kafasında ne var. Oraya gireceğiz - gerekirse onu kurtaracağız. Olay çıkarma - buranın itibarını mahvedersin.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Evet, efendim. Hanımefendinin kardeşi olduğunu söyledi.";
			link.l1 = "Ve onu içeri almadınız...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Elbette hayır! Hanımefendi son derece şık giyinmişti ve aksansız konuşuyordu, o işçiden farklı olarak. Onu kovalamaya çalıştık, ama tüm muhafızları yere serdi, düşünebiliyor musunuz?!";
			link.l1 = "Kolayca hayal edebiliyorum.   Peki, şimdi nerede?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "O ve hanımefendi hâlâ bir şeyler konuşuyorlar, ama ne hakkında olduğunu anlayamıyoruz - muhtemelen kendi dillerinde.";
			link.l1 = "Onlara gideceğim. Belki hanımefendinizin yardıma ihtiyacı vardır. Muhafızları çağırmayın - bu duyulursa, bir daha kimse kapınızı çalmaz.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Bir erkek kardeş mi? Hanımefendi asil biri, ki bu onun şu 'kardeşi' için söyleyemeyeceğim bir şey. Onun aklını karıştırmaya ya da bu işçiyle onu kandırmaya gerek yok. Onu götürün.";
			link.l1 = "Sana onların birbirini çok uzun zaman önce kaybettiklerini söylemiştim. O sadece daha az şanslı. Burada geçirdiğimiz zamanın bedelini kendimiz ödeyeceğiz. Hemen hanımefendiyi haberdar et.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Senin yanında endişelenecek bir şeyi yok. Ve senin ısrarcılığını hiç sevmiyorum. Çocuklar! Şu işçiyi dışarı atın! Bir de onun yanlış yola sapmış efendisini!";
			link.l1 = "Lanet olsun! Bir fahişede ne kadar da kibir var!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Olmaz! Hanımefendiyi, sizin bu tuhaf arkadaşlarınızla baş başa bırakmak mı? Ancak tek başınıza giderseniz, monsieur. Ve... dostlarınız dışarıda beklerler - burası saygın bir mekandır.";
			link.l1 = "Onun için neden endişeleniyorsun? Herkes onun Tortuga'nın en iyi kılıç ustalarından biri olduğunu bilir. Ve arkadaşlarım bu kasabadaki çoğu insandan daha düzgün insanlardır.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Çocuklar! Burada yaralı bir haydut ve pis bir işçi var! Hanımımızdan bir şey istiyorlar! Onlarla ilgilenin!";
			link.l1 = "Ne adanmışlık, kahretsin...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Sanırım siz Charles de Maure'sunuz? Ve bu... Ah.";
				link.l1 = "Ve sen Belle Etoile olmalısın. Yoksa Chang Xing mi demeliyim? Evet, bu senin kardeşin. On yılı aşkın süredir seni arıyor. Onunla birlikte sana soracak çok, çok sorumuz var. Ve fazla vaktimiz yok.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Aman Tanrım, hayatta kaldın. Biraz geç kalsa da, yanında iyi bir koruyucun var. Beni koruyucusu sanan ve şimdi yanında duran kişiden kesinlikle daha iyi. Şans senden yana, sevgili kızım.";
				link.l1 = "Belli ki biliyorsun. Bu daha da iyi - açıklamaya gerek yok. Ama söyle bakalım, neye gülüyorsun Chang Xing? Başka kızların acı çekmesini izlemek hoşuna mı gidiyor? Sonuçta onları sen satıyorsun.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, değil mi? Sizinle görüşmek istediğinizi duydum. Peki, sizi ne rahatsız ediyor? Geçen sefer buraya geldiğinizde hizmetimizden memnun kalmadınız mı?";
				link.l1 = "Az önce başka bir mekânınızdan geldim, Chang Xing. "+sStr+", sevgilim, öldü. Ve biliyorum ki bunda senin de payın var.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Bu ismi duymayalı çok zaman oldu. Gerçekten çok zaman geçti. Beyazlar... hep acele edersiniz. Peki ya sakin bir aile buluşması? Umurumda değil gerçi. Yıllar önce insanlara güvenmeyi bıraktım. Neden hiçbir şey söylemiyorsun, kardeşim? Kendi öz kardeşini gördüğüne sevinmedin mi? Sonuçta beni bulmak için ne kadar uğraştın.";
			link.l1 = "Başka acil ve daha önemli işlerimiz var. Kız kardeşinle konuş, Longway. Ama gitmemiz gereken yeri unutma. Acele etmeliyiz. Ona benim de soracaklarım var.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(Mandarin dilinde) Longway, ha? İsmin dışında pek değişmemişsin... Chang Tu.";
			link.l1 = "(Mandarin dilinde) Ama çok değişmişsin, abla. Ne oldu sana? Eskiden bakışların öğle güneşi gibi sıcaktı. Şimdi ise soğuk ve sadece küçümseme var içinde. Ya sesin? Eskiden seni güldürmeyi, o gümüş çanların sesini duymayı severdim... Şimdi ise kışın Goango’dan bile daha soğuk. Onların kıyafetlerini giyiyorsun. Kadınları kendin satıyorsun, oysa bir zamanlar seni Fermentelos kaçırmıştı.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Bana akıl vermeye mi geldin, oysa sen bir zamanlar takımadaların en büyük alçaklarından Rodenburg için çalıştın? Hakkında hiçbir şey bilmediğimi mi sandın? Hep biliyordum. Ne hale geldiğimi ve neden böyle olduğumu yargılamak sana düşmez, yolunu şaşırmış ağabeyim.";
			link.l1 = "Bırak ben öğreneyim, Xing! Ve bana söyle. Eğer benim Takımadalar'da olduğumu biliyordun, neden bunca yıl sonra benimle buluşmak istemedin? Tüm hayatımı seni aramaya adadım...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Çünkü ne sen ne de Tanrı beni en korkunç sondan korudu. Sonra anladım ki bu dünyada kimsenin kimseye ihtiyacı yok. Sadece kendimize güvenebiliriz. Peki, bilmek istiyorsan anlatırım. Ama onun dilinde konuşacağım. Eminim o da duymak isterdi. Fransızca anlıyorsun, değil mi, Tu?";
			link.l1 = "(kırık Fransızca ile): Evet, o dili konuşuyorum.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, ah, Tanrım! Aksanınız berbat. Ama bu sizin suçunuz değil - Fransızca telaffuzu ve yazımı gerçekten zordur.";
			link.l1 = "Şimdi farklı gülüyorsun, kardeşim...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			ReturnOfficer_Longway();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Sevgili kardeşim, yıllar içinde bana ne olduğunu öğrenmek istiyor. Sanırım senin de dinlemen iyi olur - dediğin gibi, soruların var. O yüzden endişelenme - sana her şeyi Fransızca anlatacağım.";
			link.l1 = "Bana sadece özünü anlat - Longway bana hayat hikayesini anlattığında saatler sürdü. Ve şimdi acelem var.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Sabrınız olacak. Ben bunu bir yıldan fazla içimde tuttum. Ve eğer sözümü keserseniz, hiçbir sorunuza cevap vermem.";
			link.l1 = "Peki... O zaman devam et.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Ne oldu senin görgüne, Charles de Maure? Bana senin mükemmel bir görgüye sahip, hanımların gözdesi biri olduğun söylenmişti. Sadece dedikoduymuş, gerçekte ise... tam bir fiyasko? Ben de öyle düşünmüştüm. Ve yanılıyorsun - ben hem erkeklerden hem kadınlardan eşit derecede nefret ederim. Aslında, kimseye güvenmem, merak etmem, hiçbir şey beklemem. Elime geçirsem, senin taşşaklarını ezmekten zevk alırdım. Ama bunca yıl sonra gerçek adımı duymak biraz... ferahlatıcıydı.";
			link.l1 = "Ben kadınlar için bir adamım, senin gibi cadılar için değil. Hem zaten, en çok değer verdiğim insana işkence etmene ortak olduğun düşünülürse, ne bekliyordun ki? Sana da bir şey yapmamak için kendimi zor tutuyorum. Hem de onun hatırı için. Longway benim dostum. Ve sen onun ailesisin. On yıldan fazladır seni arıyor. Seninle konuşmayı hak ediyor.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Ne kadar duygusal. Ve ne yazık ki umurumda değil. Ama artık bu kadar kolay kurtulamayacaksın, değil mi, Tu? Seni öldürdüğüm için ya da hepinizin bir kere geç kaldığı için değil. Ama bilmek... Sanırım bunu bilmeye hakkın var. Ben böyle değilken beni tanıdın, kardeşim.";
			link.l1 = "Sana ne olursa olsun... her zaman bir seçeneğin vardı, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Hâlâ gençsin ve dünyanın nasıl işlediğini bilmiyorsun, Charles de Maure. Hayatta tek gerçek seçim vardır: yaşamak ya da ölmek. Bence her şeyi bilmen de senin için iyi olurdu. O yüzden hikayemi Fransızca anlatacağım. Konuşuyorsun, değil mi, Tu?";
			link.l1 = "Aksanlı konuşuyor. Ama çok iyi anlıyor. Başlayabilirsiniz.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "Ve bunca zaman neredeydiniz? Espanola sadece bir-iki gün uzaklıkta. Onun ölümü de sizin suçunuz. Hem sen. Sen de on yıldan fazla geciktin. Kurtarıcılarımız, koruyucularımız. Bir kadın kendini ne kadar erken savunmayı öğrenirse o kadar iyi. Bazıları zamanında öğrenir, bazıları öğrenemez. Ve bazıları bunu anlamak için yeterince akıllı değildir.";
			link.l1 = "Söyleyeceğin her kelimeye dikkat et. Seni hâlâ paramparça etmediysem, sadece dostum için, yani senin kardeşin için. Onun senin için neler yaşadığını hayal bile edemezsin.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Onun benim yaşadıklarıma uzaktan yakından benzer bir şey yaşadığından ciddi şekilde şüpheliyim.";
			link.l1 = "Bize anlat.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Ne diyebilirim ki, o zamanlar gençtim, aptaldım ve safdım. Bir de tahammülsüzdüm. Tu sana zaten Oliverio Fermentelos’un, ailemi öldürdükten sonra beni nasıl kaçırdığını anlattı mı?";
			link.l1 = "Evet, doğru.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Bana kur yaptı ve duygularını itiraf etti, ama onu reddettim. Ve işte o zaman ailemizi katletti ve beni kaçırdı. Ve sonra...";
			link.l1 = "Tahmin edebiliyorum.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Keşke yapabilseydin. Sonra bana tekrar duygularını itiraf etti, ateşli ve gözyaşları içinde, bunun tek yol olduğunu söyledi, çünkü ailem asla onunla gitmeme izin vermezdi.";
			link.l1 = "Delilik...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, o zamandan beri bütün hayatımı anlatan bir kelime bu. Onu yine reddettim. Ve bir süre böyle devam etti. Ama belli ki sonsuza dek süremezdi, çünkü tamamen onun insafına kalmıştım.";
			link.l1 = "Yani gerçekten oldu mu?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Elbette. Beni zorla aldı, acımasızca ve hoyratça. Tecavüzcülerin umurunda olmaz zaten, ama daha önce bana büyük aşkını gözyaşlarıyla itiraf etmemiş miydi? Pöh! Demek ki o aşk çoktan bitmiş. Ve bütün bunlar her gün, sanki sıradan bir şeymiş gibi devam etti. Başta bağırdım, direndim, ama sonra bıraktım - zaten ne anlamı vardı ki...?";
			link.l1 = " Ama Fermentelos hak ettiğini buldu, ve sen de burada buldun kendini. Nasıl oldu bu?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Pek yakında benden bıktı. Komik, değil mi? Benim ve Tu'nun anne babasını öldürdü, beni kaçırdı, defalarca onurumu çiğnedi, sonunda ise beni bir kenara attı. Bu Takımadalara geldi ve beni Levasseur'a köle olarak sattı.";
			link.l1 = "Bunu düşmanıma bile dilemem. Peki nasıl hayatta kaldın? Ve en başta nasıl özgür kaldın? Duyduğuma göre Levasseur kadınları asla sığınağından çıkarmazmış. Onlardan hep kurtulmuş.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "Şimdi işler böyle. Levasseur o zamanlar farklıydı. Hayır, o her zaman bir hayvandı. Ama başlarda, ara sıra yerli genç kolonistleri kaçırır, bodrumunda onlara tecavüz eder ve susturmaları için para ödememek adına hemen ortadan kaldırırdı. O yıllarda nadiren birkaç günden fazla tutardı onları. Ama bana gelince, en başından beri her şey farklıydı.";
			link.l1 = "Çünkü köleydin, değil mi?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Kesinlikle. Levasseur'un asıl arzusu sadece bedensel haz değildi. Hatta kurbanları üzerindeki anlık güç hissi bile değil – sonuçta tüm adaya hükmediyor. Ama...";
			link.l1 = "... onları kırılırken izlemekten alınan haz - iradeleri, bakışları, sesleri, davranışları.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Evet. Görüyorum ki ödevinizi yapmışsınız, Kaptan. Ama bu konuda ona hiç eğlence olmadım - Fermentelos beni zaten kırılmış halde getirdi. Ve Levasseur beni güzel bulmadı - Asyalı kadınlardan hoşlanmaz. Biliyor musunuz, nedense bu beni çok etkiledi - çekici olduğumu biliyorum, ama gerçekten güzel olduğumu düşünmüyorum. İnsanlar bana bunu söylediklerinde de inanmıyorum. Şimdi bile, egzersiz yaparken, ipekler giyerken ve kendime güzel parfümler sıktığımda. İşkencecimin onayına ihtiyacım yok tabii, ama...";
			link.l1 = "Pekala, o zaman sorumu tekrar soracağım - nasıl hayatta kaldın? O adam bir kadından sıkıldığı anda ondan kurtulur. Seninle ise, dediğine göre, başından beri sıkılmıştı.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Sanırım başından beri onu sıkmamın da etkisi oldu. Bir de köleydim - hiçbir yere gidemez, hiçbir şey söyleyemezdim. Köle kızlara binlerce yıldır böyle davranılıyor. Benimle geçirdiği zamanı kendisi için ‘eğlenceli’ hale nasıl getireceğini düşünmeye başladı.";
			link.l1 = "Belli ki bağımlılıkları böyle ortaya çıktı, şu anki halleriyle.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Kesinlikle. Başta dayak, tükürük ve başka aşağılamalar vardı. Ve alaylar – hem dış görünüşümle hem de kökenimle, kanımla dalga geçtiler. Sonra ilk işkenceler başladı – bıçaklar, kerpetenler, bir tava... Bu yüzden böyle kapalı kıyafetler giyiyorum – tüm vücudum yara izleriyle, yanıklarla ve sakatlıklarla dolu. Ve bu yüzden bir daha asla bir erkeğin önünde soyunmayı düşünmüyorum. Asla. Sonra nihayet, Fermentelos beni kaçırdığı zaman anlamam gereken şeyi anladım.";
			link.l1 = "Ne oldu o?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Artık çaresiz bir kukla olmamalıydım. Tam tersine, hayatımın kontrolü bende olmalıydı. Benim için, bir kadının hayatını değiştirmesinin tek yolu, etrafındaki erkekleri kontrol etmekten geçiyordu.";
			link.l1 = "Levasseur'ün kontrol altına alınabileceğini söyleyemem.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "Ve yanılmış olmazdınız. Ama ona dikkatlice etki etmek mümkün. Levasseur, baştan sona tam itaatten de, tartışmadan ya da yalvarmadan da eşit derecede nefret eder. Aynı şekilde pohpohlanmaktan da - muhtemelen aslında ne kadar aşağılık biri olduğunu fark ettiğinden. Bunu hemen, oldukça acı bir bedelle anladım. Ama, işkence ve şiddetle geçen bir başka akşamdan sonra her şeyden memnun kaldığında, onunla nazikçe konuşmak mümkündü. Soylu biri olmayabilirim, ama zekâmdan da yoksun değilim.";
			link.l1 = "Ve ne konuştunuz?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Onun ilgisini çektim. İşkence için fikirler sundum, hangi işkence aletlerinin kullanılmaması gerektiğini, hangileriyle başlanmasının daha iyi olacağını söyledim. Başta elbette hepsini önce benim üstümde denedi. Ama sonra... bana, kendi sapkın tarzında, saygı duymaya başladı. Kafasında neler dönüyor? Nasıl böyle biri olduğunu öğrenmeye çalıştım ama beni yine ölümüne dövdü. Sonra da bana özel bir doktor getirdi.";
			link.l1 = "Bu, onun hakkında şimdiye kadar duyduklarımdan bile daha tuhaf ve iğrenç.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Artık kendimi ona teslim etmemi istemiyordu. Bana öğrencisi diyordu. Ama her zaman, onun projesi olarak tam bir hayal kırıklığı olduğumu söylerdi. Sanırım beni tetikte tutmak için. Sonra bana eskrim ve diller öğretmeye başladı. Beni bodrumda tutmasına rağmen, pahalı elbiselerin hepsi karısına değil, bana gelirdi.";
			link.l1 = "Gerçekten de bir proje. Yeri yönetme şeklinizle açık bir paralellik görebilirsiniz.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Bu açıdan düşünmemiştim, hmmm. Ve senin benzetmeni de beğenmedim, çünkü ben kadın çalışanlarıma işkence yapmam. Müşterilerimin de yapmasına izin vermem. O fahişelerden nefret etsem ve güzelliklerini kıskansam bile. Ve o domuzla hiçbir ortak yanım yok, bunu unutma.";
			link.l1 = "Peki bu geneleve nasıl sahip oldunuz?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Elbette Levasseur’dan. Bir süre beni yanında tuttu. Ara sıra, şu ya da bu kızı nasıl kıracağını bile sorardı. Sonuçta, ben onun için özeldim, bunu asla itiraf etmese de. Ben ilk kişiydim. Her şeyi gördüm.";
			link.l1 = "Kim kimden öğrendi, tekrar söyler misin?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Ben öyle biri değilim! Ruhumun derinliklerinden nefret ederim, her şeyi altın tepside önüne sunulanlardan! Bu adil değil! Bu genelev fikri bana aitti! Çalışanlarım, bazen Levasseur'un çevresine düşen tüccarların, memurların ve soyluların kızları. Onları bana vermesini ben istedim. Gizli bir mahzende işkence ve aşağılanmak bir şey. Ama onlar gibi insanlar için alenen fahişelik yapmak bambaşka bir şey!";
			link.l1 = "Kadın çalışanlarınızın bu kadar aşağılanmış, perişan ve kırılmış göründüğünü söyleyemem.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Çünkü Levasseur'un ya da benim onlara ne yapacağımızı çok iyi biliyorlar, tek bir ses çıkarsalar bile. Ama elbette, kısmen haklısın. Şarap, yemek, ipekler, her gün işkence görmemek - çoğu beni bir kurtarıcı olarak görmeye başladı. Aptallar! Burada olmaktan memnun olmayan çok azı var. Bazılarını ise, ağır bir yürekle elden çıkardı. Ve gülerdi, her zaman ona geri verebileceğimi, karşılığında yerimin para sorununu çözeceğimi söylerdi. Ama ben hep reddettim. En azından bu şekilde, boş yere mahzende ölmek yerine altınla geri dönerlerdi. Bu, onlar için fazla kolay bir çıkış olurdu.";
			link.l1 = "Ne yazık ki herkes aşağılanmış hissetmedi, Engizisyon'dan beter manastırları senin genelevin gibi altın bir kafese değişmek...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Beni mi yargılıyorsun? Sadece hayatta kalmak değil, başarılı bir ticaret kurmak istedim. Farkında olmadan da olsa, Levasseur bana minnettardı. Artık köle olmasam da, beni bırakmasına izin veremezdi. Hâlâ onun için çalışmaya ve adamlarına yardım etmeye zorlandım. Özellikle de her gördüğünde bana sarkıntılık eden o cılız yeğeni. Ama bana saldırmaya ya da kötü konuşmaya cesaret edemezdi. İğrençti. Biliyor musun, beni hayal kırıklığı olarak görse de, Thibaut ve Martene'in toplamından daha faydalıydım. O zamanlar Port-au-Prince'de olduğu gibi, onun emriyle onlara sık sık eşlik ettim.";
			link.l1 = "Bu, pek çok şeyi açıklıyor...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Doğru. Dinle. Sevgilini ben işkence etmedim. Bu ellerimle hiçbir kıza işkence etmedim, bazen Levasseur'a akıl vermiş olsam bile. Ama madem konu açıldı...";
			link.l1 = "Ne?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Bildiğiniz gibi, Levasseur bazen Tortuga'da görülen ve sonra adadan ayrılan belirli bir kızı kendisine getirmemizi isterdi. Ya da birisi onu şaşırtmak için, gözüne girmek amacıyla ona yabancı birini getirirdi, benim başıma geldiği gibi. Sevgilinizi kaçırmak benim fikrimdi.";
			link.l1 = "Ne dedin az önce...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, o köpeği, ona melez kadını, Lutter'ın karısını getirecekti. Ama sen Sotta'yı öldürdün, yani büyük adama melez yok. Levasseur deliye döndü. Herkes dayak yedi - Thibaut, Martene, hatta ben bile. Beni daha çok kim kızdırdı bilmiyorum: yine beni döven o mu, yoksa buna sebep olan sen mi... "+sStr+"";
			link.l1 = "Yani bu onun yüzünden bile değilmiş... Bunu sen yaptın.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Affınızı ummuyorum bile, dahası, buna ihtiyacım da yok. Kan istiyorsanız, kan alacaksınız. Ve buna çok pişman olacaksınız. Ama anlayıştan vazgeçmem. Uzun on yıldan sonra ilk kez buna ihtiyacım var. Yaptığım tek şey, bir gün Tortuga'dan kurtulmak için elimden geleni yapmaktı. Bana sormak istediğiniz bir şey var mı, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Ama kaçırılma olayına sen de karıştın. Ve Levasseur'un kurbanlarını nerede tuttuğunu biliyorsun. Bana yerini söyle. Eğer en kötüsü olmadıysa - sana karşılık vermemeyi ciddi ciddi düşüneceğim.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Eh, sonunda her şey bir araya geliyor...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Oradaydım, o yüzden biliyorum. Eğer onunla aramda karşılıklı ve sağlıksız bir bağ olduğunu düşünüyorsanız - fena halde yanılıyorsunuz. O domuzun birinin elinde şişe geçirilip kızartıldığını görmek beni mutlu ederdi.";
			link.l1 = "Vaktim yok, Chang Xing. Nerede?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Şehir sokaklarının altındaki yerel zindanı biliyor musun? İşte oraya gidiyorsun. Kör noktalardan birinde büyük bir şarap fıçısı var, hemen yanında ise onun zevk odasına açılan gizli bir geçit başlıyor, arada bir oraya böyle der.";
			link.l1 = "Eh, sonunda her şey bir araya geliyor...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Aferin sana. Şimdi defol. Yıllar sonra konuşmak istemiş olsam da, bütün sırlarımı bildiğini, bana yapılanları öğrendiğini fark etmek... iğrenç bir his. Seni görmek artık sadece öfkelendiriyor beni. Ha, bir de Tu burada benimle kalıyor.";
				link.l1 = "Neden böyle?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Belki de onun ailesi olduğum içindir? Bir de senin yanında nasıl biri olduğuna bakıyorum – ezilmiş, mutsuz, dili tam öğrenememiş, doğru düzgün konuşamayan bir adam. Oysa bana sizin arkadaş olduğunuzu söyledi. Ona nasıl etki ettiğin açıkça ortada. En azından ben onu adam edeceğim.";
			link.l1 = "Ve kendinle gerçekten mutlu musun? Ondan ne yaratacaksın? Hayatları pazarlayan acımasız, kin dolu bir yaratığa mı dönüştüreceksin?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Efendim Kaptanım, lütfen durun. Sizden kardeşimi rahat bırakmanızı istiyorum. Ve... ben onun yanında kalacağım.";
				link.l1 = "Sen... ne? Longway... ama neden? Onun neye dönüştüğünü görmüyor musun?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Sen farklı mısın? Zamanla değiştin. Hem de kötüye. Başta kibardın, anlayışlıydın. Ama sonra kaba oldun, Rodenburg’dan bile daha kabaydın. Ve Van der Vink’i yakalamak için iyi bir gemiye ihtiyacım olduğunda, bana bir hurda verdin!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Bir zamanlar denize açıldım ve tüm bu yılları kız kardeşimi bulup kurtarmak için harcadım. Ve şimdi o burada ve güvende. Görevim tamamlandı. Ve... Benim adım Chang Tu. Longway, bana hain Van Merden tarafından verilen isim, unuttuysan hatırlatayım. Ama Chang Tu özgür bir adam. Chang Tu'nun uzun yolculuğu nihayet sona erdi.";
			link.l1 = "Seni tıpkı bir zamanlar Rodenburg'un yaptığı gibi hizmetkâr yapacak. Aile olduğun için sana baskı kuracak. Ve sen, bana bunları yaşatanın tarafını bu kadar kolay mı tutacaksın? "+sStr+" bu kadar çok acı mı?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Şu anda Chang Tu'ya baskı yapan sensin. Lütfen, bırak gideyim. Çok yorgunum. Sen iyi bir insansın, Kaptan - buna gökler şahittir. Ama sen benim ailem değilsin. O ise öyle. Eğer kalmazsam, bunca yıl boşa geçmiş olacak. Şimdi onun yol gösteren yıldızı olacağım ve sönmüş ateşini yeniden yakacağım - yakıp yıkan değil, sıcak ve huzur veren bir ateş.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, haklısın. Belki de şu anda fazla zorluyorum. Neyse, sana her zaman saygı duydum. Umarım kız kardeşinle uzun zamandır beklediğin aile buluşmasını yaşarsın. Ama seni uyarıyorum, onun yanında huzur bulamayacaksın.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Beni şimdi bırakamazsınız! Hâlâ kurtarmam gereken biri var "+sStr+" Levasseur'dan! Oraya tek başıma gitmemi mi istiyorsun? Bana yardım et, Longway. Sonra seni serbest bırakacağım. Sana söz veriyorum.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Bununla başa çıkabilirim. Artık benim için endişelenmene gerek yok. Teşekkür ederim.";
				link.l1 = "Kız kardeşiniz, barışçıl bir şekilde ayrılmaya karar verdiğimiz için öfkeli görünüyor.";
			}
			else
			{
				dialog.text = "Bunu çözeceksiniz, Efendim Kaptanım. Gördüğüm en zeki adamsınız. Kadınlara eziyet etmekten başka bir şey bilmeyen o serseriyi kolayca alt edersiniz. Size yalvarıyorum, beni buna zorlamayın. Kız kardeşimin bana anlatacağı çok şey var! Ve... adım Chang Tu.";
				link.l1 = "Şimdi beni terk ederek bana ihanet ettiğinin farkındasın, değil mi?! Özellikle de bütün bunların başlamasına sebep olan o kadınla kalmayı seçerek!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Korkmayın, Kaptan. O benim hakkımda saygısızca konuşsa da, ben onun ağabeyiyim ve son erkek akrabasıyım. Gidebilirsiniz. Sizi öldürmesine izin vermem. Elveda.";
				link.l1 = "Elveda... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Söyleyecek başka bir şeyim yok. Hoşça kalın, Kaptan. Size de bol şans. Chang Tu her zaman özgür bir adam olacak. Bunu unutmayın.";
				link.l1 = "Ve ben her şeyimi bırakıp sana yardım ettikten sonra bana reva görülen bu mu?! Onların bana yaptıklarından sonra "+sStr+" şimdi mi?! Sen bir hain, Chang Tu. Ve ikiniz de öyle öleceksiniz, lanet olası yılanlar!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Benim adım Chang Tu. Longway öldü. Onu sen öldürdün. Artık benim kaptanım değilsin. Ve şimdi öleceksin. Ailem sonunda huzur bulacak ve yıldızımız gece gökyüzünde parlak parlayacak.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Güvenilir) (Liderlik) Longway... Chang Tu. Dur. Senin için mükemmel bir Kaptan olmadığımı biliyorum. Ama gerçekten, bunun için beni öldürmek bu kadar mı istiyorsun? Bunca yaşadıklarımızdan sonra? Önce Rodenburg, şimdi de kız kardeşini arıyoruz.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				Notification_Perk(true, "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, ben senin Kaptanınım. Ailen değilim, bakıcın da değilim. Ben emir veririm, seni istemeden kırıp kırmadığımı düşünmem. Taleplerini sanki yıllardır evliymişiz gibi sıralıyorsun, Allah aşkına...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Evet. Şimdi anlıyorum. Sen de sadece kendini düşünen, çürümüş bir pisliksin... Longway. Tıpkı kız kardeşin gibi. Benim ailem bu günü atlatacak. Seninki - atlatamayacak. Cehenneme git!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Eğer seçim seninle ailem arasında olacaksa - yine de ailemi seçerim, ne kadar zor bir karar olsa da.";
			link.l1 = "Onca yıl boyunca onu ararken parmağını bile kıpırdatmayan bir aile mi? Ama işte, doğru zaman gelince birden ortaya çıktılar! Oysa ben, sana yardım etmek için her şeyimi feda ettim. Şu an burada duruyor olman bile bunun sonucu. İnan bana, ben sana ondan daha çok aileyim, dostum!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Haklısınız. Her zamanki gibi, yine haklısınız. Beni affedecek misiniz, Efendim Kaptanım?";
			link.l1 = "Affedilecek bir şey yok! Bir konuda haklısın – sana layık bir Kaptan değildim her zaman. Sanırım artık ödeşmiş olduk. Bu arada, bundan sonra sana nasıl hitap etmemi istersin? Longway mi? Yoksa Chang Tu mu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Bırak Longway olsun. Zaten bana öyle hitap etmene alıştım.";
			link.l1 = "O halde tüm anlaşmazlıkları unutalım ve tekrar hoş geldin, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Sen! Ne diyorsun?! Neden durdun?! Öldür onu! Onun gözünde hep bir işçiden fazlası olmayacaksın! Ailen benim ve sadece benim!";
			link.l1 = "O kadar öfkeli ki, değil mi Longway? Artık onun ailesi değilsin, Xing. Longway’in Takımadalar’a geldiğini öğrendiğinde bunu görmezden seçtiğin anda her şey bitti. Gidiyoruz.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Sanırım o köle zihniyetini ondan tamamen söküp atma şansım hiç olmadı. Onu kurtaramam. O zaman ikinizi de kendi ellerimle öldüreceğim.";
			link.l1 = "Burada kurtarılamayacak tek kişi sensin. Biliyor musun, sana karşı fazla anlayışlı ve affedici davrandım. Ama bu daha da iyi. Sanırım Longway bile ne kadar sinsi olduğunu fark etti. Senin için fazla yas tutmaz.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Şaka yapmanın sırası değil şimdi! Korkunu ve başarısızlığını onların arkasına saklıyorsun! Bu da beni daha da ikna ediyor. Kendini savun, de Maure! Çünkü Chang Tu seni bağışlamaya hiç niyetli değil.";
			link.l1 = "Üzgünüm, böyle bittiği için. Ama eğer sen böyle istiyorsan, öyle olsun. O halde, benden de merhamet bekleme.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, dinle...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, dur...";
				link.l1 = "Helen, şimdi arkamda dursan iyi olur. Saldırırlarsa kendimi daha güvende hissederim.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "Ama yapmazlar, değil mi? Hadi şimdi gidelim, hepsi bu. Ona bunca şey yaptıktan sonra hâlâ böyle düşünüyorsa, fikrini değiştirmeye çalışmanın anlamı yok. Sözlerden çok, yaptıkların önemlidir. Kız kardeşiyle kalmak istiyorsa, bırak kalsın.";
				link.l1 = "Helen, onun yüzünden çok acı çektin...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "O şeytan kadını kendi iblisleriyle baş başa bırak. Onlar yakında onun ruhunu tüketecekler. Bizimkiler ise iyi bir dinlenmeyi hak ediyor. Hadi gidelim.";
				link.l1 = "Evet. Sanırım öyle yapmalıyız. Hadi buradan gidelim, meleğim. Ve sen - Longway ya da Chang Tu - hoşça kal.";
			}
			else
			{
				dialog.text = "Ama ölmedim. Ve en kötüsü olmadı. Buradayım, seninleyim, önemli olan da bu. Levasseur öldü. O olmadan, o kadın hiçbir şey. Mekânı zarar ediyor ve yakında batacak. Onlar da onunla birlikte yok olacaklar. Hadi gidelim, benim kaptanım. Burada yapacak başka bir şeyimiz kalmadı.";
				link.l1 = "Tartışmayacağım, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Nereye gidiyorsun?";
			link.l1 = "Ne oldu, seninle kız kardeşinin ciğerlerini dökmek için can atmadığımıza şaşırdın mı, Longway? İşte aramızdaki fark bu. Ve hâlâ kötü adamın ben olduğumu düşünüyorsun... Ama tamam, bak. Eğer beni öldürmek istiyorsan, Helen’i de öldürmen gerekecek. O yaralı, sakat. Bunu gerçekten yapmak istiyor musun?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Hı hı.";
			link.l1 = "Gözlerinde şüpheyi görebiliyorum, bana karşı bir sürü kin beslediğini de biliyorum. Ama gel, Helen'den örnek alalım, ne dersin? Mürettebatımızda ondan daha iyi kalpli ya da affedici biri yok. Gidiyoruz. Eğer içinde biraz olsun iyilik ya da sağduyu kaldıysa, yolumuza çıkmazsın.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Öyle olsun. Özür dilerim. Ama artık benim Kaptanım değilsiniz.";
			link.l1 = "Bir şekilde atlatırım. Kardeşin ne yapmış olursa olsun, sana ve ona en iyisini dilerim. Hoşça kal, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Hadi Charles, bu isyanı bastırmanın zamanı geldi.";
			link.l1 = "Tanrı biliyor ki bunu yapmak istemedim... ve hâlâ istemiyorum.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Yapmaz mısın?! Charles, beni dinle. Onun için o kadar çok şey yaptın, peki karşılığında ne aldın? İhanet ve çirkin sözler, di mi! Gerçekten bunu görmezden mi geleceksin?";
			link.l1 = "Longway'ın kanını dökmek istemiyorum. Bir zamanlar arkadaş olduğumuzu unutmadım.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Böyle dostlar batsın - düşmandan beterler, di mi! Charles, bana bak. Bana ne olduğuna bak - şu lanet adaya gelirken bana hakaret eden, aşağılayan, alay eden o kız kardeşi yüzünden!";
			link.l1 = "Mary, anlıyorum - şu anda çok, çok öfkelisin...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Ah Charles, sadece kızgın değilim, hayır... öfkeliyim! Ve bu sadece o sefil herifin sana söyledikleri yüzünden değil! Bana bir daha bak, Charles—ve düşün, eğer buna şimdi ve burada bir son vermezsek, daha kaç kız bu acıyı yaşayacak.";
			link.l1 = "Artık kimseye zarar veremeyecekler. Levasseur öldü.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, o kadının saçmalıklarını gerçekten dinledin mi? O da o pis domuz kadar bodrumda olanlardan sorumlu. Şimdi Longway’e bak - ya da artık adı her neyse. Gördün mü, onu ne kadar çabuk kendi tarafına çekti, di mi! Kim bilir daha ne hastalıklı fikirler sokacak o hainin kafasına? Sence o şeytan kadının, onu Levasseur’un yoluna itmesi çok mu zor olacak? Şu an ne olduğuna bakma, Charles. Bir yıl... hatta bir ay sonra ne tür bir canavara dönüşebileceğini düşün. Haklı olduğumu biliyorsun, değil mi?";
			link.l1 = "İtiraf etmekten nefret etsem de, sana karşı çıkacak hiçbir şeyim yok, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha! Büyüleyici, ne gösteriydi ama. Uzun zamandır böyle içten gülmemiştim. Cesareti de var, hakkını teslim ediyorum.";
			link.l1 = "Kes sesini, seni kaltak.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Bu komik, değil mi, de Maure? Tu'nun seni yere sermesini kendi gözlerimle görmek isterdim. Ve bakıyorum ki senin kadının da en az benim kadar kana susamış. Çok güzel. Kenarda duracak değilim—Levasseur ve Tortuga'nın en dişli adamlarıyla çalıştım. Bakalım hangi ikili galip gelecek.";
			link.l1 = "Pek iyi bir öğretmenin olmamış. Bir de Mary'yi kızdırdın. İşin bitti. Ben burada olmasam bile, ikiniz ona karşı asla şansınız olmazdı.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Evet. Sonunda. Longway kız kardeşiyle tekrar konuşabilir mi, Efendim Kaptanım? Çok uzun sürmez.";
			link.l1 = "Elbette. Ama çabuk ol - fazla vaktimiz yok.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway, çabuk ol.";
			link.l1 = "İyi.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "Ve bana ne söylemek istiyordun, kardeşim?";
			link.l1 = "Longway senden çok hayal kırıklığına uğramış, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(Mandarin olarak) Madem tekrar konuşmak istedin Tu, neden bizim dilimizde konuşmuyorsun? Ondan mı utanıyorsun? Senin yerinde olsam, aksanından daha çok utanırdım.";
			link.l1 = "Hayır. Longway’in Lord Kaptan’dan sakladığı hiçbir sır kalmadı. Artık yok.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(Fransızca) Önce Rodenburg, şimdi de Maure. Hep bir ‘monsieur’ lazım sana. Onca yıldır burada hiçbir şey başaramadın. Dillerinden birini bile öğrenemedin. Oysa bizimkinden çok daha basitler! Hayal kırıklığı varsa, o sensin.";
			link.l1 = "Ama ben kadın ticareti yapmam. Onların kaçırılmasına ve işkence görmesine karışmam.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Ciddi misiniz? Rodenburg için yaptıklarınızı sıralamamı ister misiniz? Benim yaptıklarım, yanında çocuk oyuncağı kalır.";
			link.l1 = "Bir amacım vardı - seni bulmak. Ama sen beni görmek bile istemedin. Ve seni bulduğumda, bir zamanlar yolumu aydınlatan sıcak bir yıldız değil, bir canavar buldum.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Bir canavar mı? Belki de haklısın. Artık tanıdığın o neşeli kız değilim. Öyle kalsaydım, hayat beni paramparça ederdi. Kendi dişlerimi çıkarmak zorunda kaldım. Yıldızım çoktan sönmüş. Ama hâlâ senin kardeşinim, Tu.";
			link.l1 = "Hayır. Artık benim kardeşim değilsin.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Bunca yılın ardından beni bu kadar kolay mı bırakıyorsun? Heh... Kim bilir, belki o gün eve zamanında dönüp Fermentelos'u öldürseydin, ben de hâlâ aynı olurdum?";
			link.l1 = "Haklısın. Bunun bir kısmı benim de suçum. Bu benim sorumluluğum. Ve buna bir son vereceğim. Seni bu acıdan kurtaracağım. Bu sefil hayata son vereceğim.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Gerçekten kendi kız kardeşini öldürecek misin, Chung Tu? Başaracağını sanmam ama gerçek şu ki...";
			link.l1 = "Artık benim kardeşim değilsin. Xing on yıl önce öldü. Ve bugün, Chung Tu'nun nihayet öldüğü gün. Bundan böyle ve sonsuza dek, adım... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Önce Chang Xing'i kurtarıyoruz.";
			link.l1 = "Ne?! Anlamıyor gibisin, dostum. Kız kardeşin şu anda acil bir tehlikede değil, ama "+sStr+"   Ve size hatırlatmam gerekir mi, Chang Xing'in de Martene ve Thibaut kadar bu işte suçlu olduğunu?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Bu doğru değil! O...";
			link.l1 = "Levasseur'un ona ne yapıyor olabileceğine dair bir fikrin var mı "+sStr+" biz burada tartışırken?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ama Chang Xing'den başka kimsem kalmadı, Kaptan... Sizin aileniz hâlâ bir arada...";
			link.l1 = +sStr+" karım olmayabilir, ama bana kendi ailem kadar değerli.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing benim son yol gösterici yıldızım, Kaptan. Ayrıca, Robert Marten'den o itirafı almamda sana borçluyum.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Kız kardeşinin peşine düşeceğiz, söz veriyorum. Ama Levasseur bunca zamandır ona dokunmamış. "+sStr+"   Chang Xing'den çok daha büyük bir tehlikede. Önce onu kurtarmama yardım et, sana büyük bir iyilik borçlanacağım.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Güvenilir) (Liderlik) Kız kardeşinin peşine düşeceğiz, söz veriyorum. Ama Levasseur bunca zamandır ona dokunmadı. "+sStr+"   Chang Xing'den çok daha büyük bir tehlikede. Önce onu kurtarmama yardım et, sana büyük bir iyilik borçlu kalacağım.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						Notification_Perk(true, "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Beni dinleyin! Kız kardeşiniz güvende. Ama "+sStr+" şu anda bir sapığın elinde, kim bilir ona şimdi neler yapıyor - belki daha da kötüsünü! Sence Levasseur, kız kardeşine diğer zavallı kızlara zindanda davrandığı gibi davransaydı, ona böyle şık bir yer işletmesine izin verir miydi?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Boş tartışmalara vakit harcamayacağım. Her birimizin kendi öncelikleri var. Yine ayrılalım. Benim Tanrım bana, seninki de sana yardım etsin.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Haklısın. Sana bir borcum var. Peki, senin dediğin gibi olsun. Ayrıca, sensiz Levasseur ve adamlarıyla baş edemeyebilirim. Ama eğer bir şey olursa "+sStr+"   kız kardeşinizle uğraşırken... ";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Anlayışınız için teşekkür ederim, Efendim Kaptanım. Size bol şans dilerim!";
			link.l1 = "Ve sana da, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Boş tehditler, gerçek tehdit değildir, Efendim Kaptanım. Acele etmeliyiz, her şeye zamanında yetişebilmemiz için.";
			link.l1 = "Umarım Tanrın bunu duyar. Hadi gidelim!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Saygımdan dolayı bunu görmezden geleceğim, Efendim Kaptanım. Sadece bu seferlik. Bir dahaki sefere seni döverim. Şimdi kız kardeşimin peşine gidiyorum, senin onayın olsun ya da olmasın.";
			link.l1 = "Seninle daha fazla tartışarak zaman kaybetmeyeceğim, Longway. Sonuçta, hepimizin her şeyden daha çok değer verdiği bir şey var.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Hı-hı, tamam, Efendim Kaptanım. Ama o zaman acele etmeliyiz.";
			link.l1 = "Doğru. Teşekkürler, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Vay vay, burada kimleri görüyoruz... Kahretsin. Charles de Maure ve onun çekik gözlü iti.";
				link.l1 = "Burada tek bir it var. Görmek istiyorsan aynaya bak, sen Huguenot piçi. Ya da yeğenine bir göz at. Gerçi o daha çok kirli bir fareye benziyor.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Sana beni rahatsız etmemeni söyledim! Ah, Charles de Maure, hehehe. Ne inatçı bir küçük haşereymişsin.";
				link.l1 = "Ben böyleyim işte. Şimdi çeneni kapa ve...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Kendi geminde değilsin, velet! Bu adada tek bir adam var, o da benim!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Bunu nasıl cüret edersin, pislik!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Sakin ol, yeğenim! Monsieur de Maure birazdan görgü kurallarının ne olduğunu öğrenecek.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Sana ciyaklaman için izin mi verdim?!";
			}
			else
			{
				dialog.text = "O ateşin hepsi nereye gitti, ha, güzelim? Ah, sanırım anladım...";
			}
			link.l1 = "Ona dokunma, seni alçak!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... İstersen bağırıp bana hakaret edebilirsin, ama rüzgarda titreyen bir yaprak gibi sallandığını görüyorum. Gözlerinde korkuyu okuyorum. Seninle Henri'nin ortak noktası bu. Alınma, yeğenim.";
			link.l1 = "Haklısın, bu korku. Ama senden değil, pislik.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Elbette, elbette. Bunların hepsini daha önce de duydum – kimseden korkmazsın, de Maure. Bana bunu o söyledi. 'A-ah, Charles gelecek, Charles beni kurtaracak... Charles şöyle, Charles böyle...' İşte, Charles burada. Charles en önde oturuyor. Henri, misafirimizi rahat ettir.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Buna gerek yok, Amca. Korkarım bu sefer biraz ileri gittiniz...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Amca, bunda senin yardımına ihtiyacım olacak...";
				}
				else
				{
					dialog.text = "Onu hemen öldüreyim mi, Amca, yoksa önce izletelim mi?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Ben değildim, burada kurtarmaya gelmekte geciken Beyaz Şövalye Beyefendi'ydi. Görünen o ki gösteri bitti, ha-ha-ha-ha!";
				link.l1 = "Tanrım, hayır...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Öyle düşünmüştüm. Bu yaşa kadar nasıl hayatta kaldın? Bu arada, aynı soru sana da, de Maure.";
					link.l1 = "Seninle ilgili ne kadar çok sorum olduğunu hayal bile edemezsin, cellat!";
				}
				else
				{
					dialog.text = "Keşke küçük gösterimizi izleyen biri olsaydı... Ama sanmam ki Bay İnatçı burada bize o zevki yaşatsın.";
					link.l1 = "Tek zevk alan kişi benim - seni doğrayarak, kasap!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Hadi, devam et ve onu kaldır! Ha-ha-ha!";
			link.l1 = "Lanet olası hayvanlar, doğduğunuza pişman edeceğim sizi!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Kasap mı? Kendimi daha çok bir sanatçı, bir ressam olarak görüyorum - en azından bunu bir sanat olarak görmeye çalışır mısınız... İzleyin.\nEserimi beğendiniz mi? Gerçekten başyapıtlarımdan biri. Tam dürüst olmak gerekirse, sarışınları tercih ederim, ama bu kız... Sonunda bu çirkin saç rengi için onu affettim. Sadece saç değildi - kız tam bir ateş! Az kalsın yanacaktım. Direndi, ısırdı, vahşi bir hayvan gibi hırladı! Bana kızıl derili bir vahşiyi hatırlattı, çok eğlenmiştim onunla, gerçi uzun sürmedi...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kasap mı? Kendimi daha çok bir sanatçı, bir ressam olarak görüyorum - en azından bunu bir sanat olarak görmeye çalışır mısın... İzle.\nBak, onunla işim henüz bitmedi - bu tuvalde hâlâ çok boş alan var. Sadece güzel değil, aynı zamanda kaya gibi sert ve buz gibi soğuk. Onu bağırtmak için gerçekten biraz ter dökmem gerekti. Sonuna kadar dayandı, sırf o güzel sesini duymamdan zevk almamam için.";
			}
			link.l1 = "Hemen bırak onu, aşağılık herif.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Nereye gittiğini sanıyorsun? Bu et parçası artık benim malım. Tıpkı etrafındaki her şey gibi - bu kasaba, bu kale... Ben Tortuga'yım. Sen ve Poincy, o pis yaşlı hindi, bunu asla değiştiremezsiniz.";
			link.l1 = "Levasseur, sen...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Sizin için Signor de René de Buaduflé de Lettre.";
			link.l1 = "Umurumda değil. Kılıcını çek ve bana bir dövüşte neye değdiğini göster – bir adamla, savunmasız bir kızla değil.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "Ve sen ne adamsın! Ama haklısın, ben de bu gevezelikten yoruldum. Geri dönmek istiyorum... kadınıma. Ama son bir soru soracağım. Buraya nasıl geldin? Buranın yerini kim söyledi? Sadece bir avuç insan burayı biliyor.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Ortak dostunuz Martene, bülbül gibi şakıyordu. Aslında, mezbahada bir domuz gibi cıyakladı desek daha doğru olur...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Belki de bunu sizden gizli tutmak daha iyi olur. Korkarım bu, egonuzu incitebilir, Signor de René... bir şey.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Kurbanlarından biri, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Yalancı, alçak herif! Kimse bu duvarların dışına çıkamaz!";
			link.l1 = "Hafızanı kullan, hadi. Bir tane vardı. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Olmaz. O değil. Bazı fikirlerim o küçük şeytandan çıktı. Ah-ah, birbirimize çok şey öğrettik, hehe. Sonunda vicdanını rahatlatmaya mı karar verdi? Sanmam. Sonuçta, onun içindeki her şeyi çoktan kazıyıp çıkarmıştım!";
			link.l1 = "Şimdi seni kuruyana kadar oyacağım. Bir damla, bir damla.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "Ve bana cellat diyorsun, zavallı ikiyüzlü! Heh-heh... Ama o Cehennem'de yanıyorsa, korkacak hiçbir şeyim yok.";
			link.l1 = "Seni orada bekliyor. O alçak yeğenin de yanında. Onu hayal kırıklığına uğratmayalım.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Bu oyuncağa biraz daha zarar vermeme ne dersin? Karnını ya da boğazını keserim, sen ona ulaşmaya çalışırken kanının akışını izlerim...";
			link.l1 = "Ne dersen de, Levasseur, ne dersen de... Karın selamını gönderiyor. Ve yanında bir veda selamı.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "NE?! Kha-kha... Kahrolası Marceline... Sefil kaltak, kaltak, kaltak, kaltak!";
			link.l1 = "Öyle gerçekten. Birbirinize layıksınız. Ama onun kafası biraz daha yerinde. En azından ilk bakışta.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Onun tavuk kafasını bir kazığa geçireceğim. Ama ondan önce... oh-oh, o orospunun başına daha çok, çok şey gelecek.... Hatta yeni oyuncağımı biraz dinlendireceğim. Bekle! Daha iyi bir fikrim var. Onu Henri'ye ödünç vereceğim. Tabii ki bir süreliğine.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Gerçekten mi? Teşekkür ederim, Amca!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Önce hak et - bana şununla bir el at, ha?";
			link.l1 = "Az kalsın kendini kaybedecek.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				ReturnOfficer_Longway();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Efendim Kaptanım... Longway taziyelerini sunar. Elimizden gelen her şeyi yaptık.";
			link.l1 = "Her şey değil, yeterince bile değil.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway, Chang Xing'i bulacak. Benimle gelir misin?";
			link.l1 = "Evet, seninle geliyorum, Longway. Ama unutma - kız kardeşin de bu kanlı oyunda oldukça aktif bir rol oynadı. Onu bağışlamam için beni ikna etmek adına çok çaba harcaması gerekecek. Ve sen ona yardım etmeyeceksin. Hadi, artık bunu bitirme zamanı.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			ReturnOfficer_Longway();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, biliyordum, di mi! Geleceğini biliyordum! Hep gelirsin, değil mi?";
					link.l1 = "Bunu dördüncü kez denemek istemem, Mary... O alçaklar, onlar...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ah, Benim kaptanım, ne kadar zamanında geldiğinizin farkında değilsiniz. O... o canavarlar...";
					link.l1 = "Artık bitti, Helen. Tamam, her şey sona erdi. Aman Tanrım, sana ne yapmışlar...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, buradasın! Biliyordum, biliyordum, di mi!";
					link.l1 = "Tam yelken açmış, canımı kurtarmak için kaçıyordum, Mary. Sen... sana... yaptılar mı?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Benim kaptanım... Buradasınız... Umudumu neredeyse kaybetmiştim...";
					link.l1 = "Mümkün olduğunca hızlı geldim, Helen. Bu kadar uzun sürdüğü için üzgünüm.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Hayır, Charles, hayır. Denediler ama elimden geldiğince karşı koydum. Bu yüzden beni bu kadar fena dövdüler... Lütfen, Charles, hadi buradan gidelim... olur mu?";
					link.l1 = "Hemen, canım. Yapmam gereken son bir şey kaldı.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Yapmadılar Charles! Yapmadılar. Diğer yaralar iyileşecek. Lütfen, beni buradan götür.";
					link.l1 = "Elbette, sevgili dostum. Burada yapmamız gereken tek bir şey kaldı.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Hayır, Charles, hayır. Denediler ama tam zamanında yetiştin. Tıpkı o zamanlar gibi. Kaçıncı kez oldu bu?";
					link.l1 = "Sayısını tutmadım, Mary. Ve asla da tutmayacağım.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Buraya geldiniz... tam zamanında. En kötüsü olmadı. Şimdi, lütfen, buradan gidelim. Nereye olursa.";
					link.l1 = " Ayağa kalk, Helen. Yukarı çık. Önce şu pislikle ilgilenmem lazım. ";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "Ve saymayı bırakmayacağım. Şimdi buradan gidelim, lütfen.";
			link.l1 = "Elbette, sevgili dostum. Burada yapacak başka bir şeyimiz kalmadı. Bir şey dışında.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Ne oldu, kha-kha, cesaretin mi yok, sümüklü? Git o korkak domuzundan yardım iste...  Ya da kendin yap, sonra da Poincy'ye ne kadar cesur olduğunu anlatacak bir bahanen olur.";
				link.l1 = "Bunun yerine, herkese ne kadar korkak bir pislik olduğunu anlatmayı tercih ederim.";
			}
			else
			{
				dialog.text = "Ne yani, gerçekten kan kaybından ölmemi izlemek mi istiyorsun? Bundan keyif alıyorsun, öyle mi? Kadınına ne kadar kahraman olduğunu anlatırsın artık. Şu duvardaki iskeleti görüyor musun? Santiago'nun bankacısının karısı... Onun adamı da kendini kahraman sanıyordu, ama o sadece iyi bir çığlıkçı çıktı - onu o çarkta döndürdüğümde...";
				link.l1 = "Cesedini bunun üstünde yuvarlayabilirim, pislik, ama korkarım kıçının ağırlığını taşıyamaz.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Korkak mı? Oh, kha-kha, hadi ama...";
				link.l1 = "Zulüm korkaklığın zıttı değildir. Ama sizin gibi biri aradaki farkı bilmez.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Bu çok akıllıca. İyi dinle beni, de Maure: tıpkı o kodaman gibi öleceksin, kendi çığlıklarından sesin kısılmış, başkalarının feryatlarından kulakların sağır olmuş halde...";
				link.l1 = "Cehennemde yan, pislik.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Felsefeden pek anlamam, bunu kabul ediyorum. Şu duvardaki iskeleti görüyor musun, de Maure? O, Santiago’nun bankacısının karısından geriye kalan tek şey. O da büyük laflar etmeyi severdi, ama ben onu o çarka bağlamaya başladığımda hepsi bitti. Geriye sadece çığlıklar kaldı, neredeyse kulaklarım sağır olacaktı...";
			link.l1 = "Hadi bunu bitirelim.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Bir dakika, Efendim Kaptanım... Bu kadar acele etmeyin.";
			link.l1 = "Ne oldu, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Onu öldürme. Bu çok basit olurdu. Daha kötüsünü hak ediyor.";
			link.l1 = "Kız kardeşin için öfkelisin, dostum. Ve onun yaptıklarına ben de öfke doluyum "+sStr+"... ve ona ne yapmış olabileceğini düşünüyorum. Ama ben onun gibi bir hayvan değilim. O mangaldan közlerle onu yakabilirim, kemiklerini o çarkta kırabilirim... Zincire vurup kan kaybından ölüme terk edebilirim. Ama adamlarından birinin onu kurtarma riskini göze alamam. O riski alamam.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Bekleyin, Efendim Kaptanım. Demek istediğim bu değildi. Ben Poincy'den bahsediyorum.";
			link.l1 = "Peki ya o?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Bu hayvanı ona canlı olarak götürsen, seni nasıl ödüllendireceğini bir düşün. Üzerine altın yağdırırdı. Ama o pislik, Capsterville zindanında çürümektense burada ölmeyi tercih eder.";
			link.l1 = "Haklı olabilirsin, Longway. Ama bu pislik ile Şövalye arasında tam olarak ne yaşandığını bilmiyorum. İnan bana, bu tayfayı senden daha iyi tanıyorum. Eğer her şey dedikleri gibi parayla ilgiliyse, bu ikisi anlaşabilirler. Poincy onu bırakabilir ve başka bir adada ya da Eski Dünya şehirlerinden birinde böyle bir oda daha ortaya çıkabilir.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Kötü bir fikir değil, Longway. Ama Şövalye'nin o kadar cömert olacağından şüpheliyim... Doğasında yok bu. Ama benim için mesele para değil zaten. Kaldırın onu! Ve yaralarını sarın, vaktinden önce ölmesin.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Ama önce, sana geliyorum. Ve arkadaşına da. Sana dokunmayacağım, dar gözlü adam - zamanımı harcamaya değmezsin.";
			link.l1 = "Görüyor musun, Longway? Buna artık burada ve şimdi bir son vermeliyiz.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Bir dakika, Kaptanım, bir dakika, kha-kha.";
			link.l1 = "Ne var, Bay eski vali?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "Anahtarım bu odada bir yerde. Ofisimdeki bir sandığı açıyor. İçinde iki yüz bin gümüş ve güzel bir kılıç var. Eğer bu yetmezse, karımın yatak odasında, şifonyerde, değerli taşlardan oluşan bir koleksiyon var.";
			link.l1 = "Hmm, peki karşılığında ne istiyorsun?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Bir kurşun. Bitir işimi. Burada ve şimdi.";
			link.l1 = "Poincy Şövalyesi'ne ne dersiniz? Duyduğuma göre eski dostlarmışsınız... Onu görmek istemez misiniz?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "Poincy cehenneme gitsin! Yani, kabul ediyor musun yoksa etmiyor musun?";
			link.l1 = "Pek sayılmaz, Monsieur de... Tüm adınızı söylemek istemiyorum.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Bu da yetmiyor mu sana? Peki, daha fazlası da var...";
			link.l1 = "Kurbanlarının çığlıkları seni sağır etmiş olmalı, Levasseur. Sana söyledim, mesele para değil. Poincy'den korkmakta haklısın, değil mi? Sana ne yapacağını bilmek bile istemiyorum. Ama bu senin... sanatına bir nebze olsun karşılık olacaksa, varsın öyle olsun.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Demek ki sen de aslında böylesin, kha-kha... Benden hiç de iyi değilsin.";
			link.l1 = "Yeter. Longway - kaldır onu!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) ReturnOfficer_Mary();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) ReturnOfficer_Helena();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) ReturnOfficer_Longway();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Gemimiz... Onu gördüğüme bu kadar sevineceğim aklıma gelmezdi... tamam. Sonunda bu kâbus bitti.";
				}
				else
				{
					dialog.text = "Sonunda bitti. Şimdi nereye, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Her şeyin bittiğine inanamıyorum... Şimdi ne yapacağız, benim kaptanım?";
				}
				else
				{
					dialog.text = "Pekala, bu kadar, Benim kaptanım. Şimdi ne yapıyoruz?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Ne yazık ki, henüz bitmedi. Chang Xing... Bu hikaye, ondan cevaplarımı almadan gerçekten sona ermeyecek.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rotamızı Capsterville'e çevir. Monsieur Levasseur'un tarihe karışma vakti geldi.";
				}
				else
				{
					link.l1 = "Şövalyenin görevi tamamlandı. Ona rapor vermem gerekiyor. Bazı ayrıntıları atlayacağım ama. Tek umudum, sözünü tutması ve Michel'in serbest bırakılması...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ben de geliyorum, di mi. Yani seninle geliyorum. Ve benimle tartışmaya bile kalkma, Charles.";
				link.l1 = "Mary, canım, dinlenmen lazım. Bayılmana ramak kaldı...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Seninle geleceğim.";
				link.l1 = "Helen, o şeytanın elinde neredeyse ölüyordun. Ayakta zor duruyorsun...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Sana ihtiyacım var, Charles. Senin de bana ihtiyacın var. Ve bu gece bayılacak biri varsa, o da Chang Xing olacak. Kendi genelevinin zemininde, gözlerinin ortasında bir kurşunla!";
				link.l1 = "Evet, Levasseur dövüş ruhunu senden alamamış. Seni gemiye geri göndermek isterdim, ama biliyorum ki yine de peşimden gelirdin...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ama hâlâ kılıç tutabiliyorum. Charles, orada olmam lazım. Onu bunu yapmaya iten şeyi anlamam gerek. Bunun benim için neden bu kadar önemli olduğunu anlıyor musun?";
				link.l1 = "Dinlenmeye ve iyileşmeye ihtiyacınız olduğunu anlıyorum. Hem de uzun bir süre.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Beni çok iyi tanıyorsun Charles, di mi. O zaman lafı uzatmayalım ve bunu bitirelim.";
				link.l1 = "Sen bilirsin. Ama tetikte ol. Dışarıda bizi ne gibi sürprizler bekliyor, kimse bilmiyor.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Bekleyebilir. Beni almaya geldin, şimdi de ben seninle geliyorum. İstesen de istemesen de.";
				link.l1 = "Hâlâ cesaretini koruyorsun, Helen. Güzel. Arkama geç, ve Allah aşkına, dikkatli ol.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Gemimiz... Tekrar ona bineceğime inanamıyorum, di mi...";
					link.l1 = "Seni bekliyor, Mary. Güzel bir yemek ve yumuşacık bir yatak da...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Kendi ayaklarımla tekneye varacağımı hiç düşünmemiştim.";
					link.l1 = "Sen tanıdığım en dayanıklı insansın, Helen. Şimdi içeri gir ve sonra da yat...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Gemimiz... Tekrar ona bineceğime inanamıyorum, di mi...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Kendi ayaklarımla tekneye varacağımı hiç düşünmemiştim.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Rotamızı Capsterville'e çevirin. Monsieur Levasseur'un tarihe karışma vakti geldi.";
				}
				else
				{
					link.l1 = "Şövalyenin görevi tamamlandı. Ona rapor vermem gerekiyor. Ama bazı ayrıntıları atlayacağım. Yeter ki sözünü tutsun ve Michel serbest bırakılsın...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ve sen, Charles... Nedir o bakış? Yine bir şeyler peşindesin, değil mi?";
				link.l1 = "Chang Xing. Ona da ulaşmam gerek.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ya sen? Nereye gidiyorsun?";
				link.l1 = "Chang Xing'i görmek. Bu kâbusun son bölümü o.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "O zaman ben de geliyorum! Bana büyük bir borcu var, di mi?";
				link.l1 = "Mary, canım, tekneye zar zor yetişebildin. Şu anda kılıç tutacak halde değilsin. Sana yaptıklarının bedelini ona ödeteceğim, Tanrı şahidim olsun. Ama senin güvende olduğunu bilerek gemide kalırsan, kendimi çok daha iyi hissedeceğim.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Benim kaptanım, seninle gitmeyi öyle çok isterdim ki... Lütfen dikkatli ol. Kim bilir daha nelere kadir? O beni tutarken o köpek Thibaut...";
				link.l1 = "En kötüsü geçti, Helen. Her şey yakında bitecek, söz veriyorum.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "En azından ben yokken Longway yanında olacak. Ama sana bir şey olursa, onu da Chang Xing'i de kendi ellerimle toprağa gömerim!";
					link.l1 = "Her şey yoluna girecek. Şimdi git, dinlen. Göz açıp kapayıncaya kadar dönerim.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Longway nereye gitti, Charles?";
					link.l1 = "Bensiz Chang Xing'in peşinden gitti. Onu durduramadım, ama ne yapabilirdim ki?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "En azından Longway seninle geliyor. Bu da bir nebze olsun teselli.";
					link.l1 = "Gördün mü? Endişelenmene gerek yok. Uzun sürmeyecek.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Longway nerede? Şimdi fark ettim, burada yok.";
					link.l1 = "Ben olmadan kız kardeşine gitti. Onu suçlamıyorum. Bu anı çok uzun zamandır bekliyordu.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, içimde kötü bir his var...";
				link.l1 = "Biliyorum. Bu kâbus çok uzun sürdü, ama artık sonu yakın. En kötüsü geçti.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kim bilir aklından ne geçiyor, Charles? Gözünü dört aç, di mi?";
				link.l1 = "Geleceğim. Yakında döneceğim, Helen."link.l1.go ="PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Bana söz ver, her şeye hazır olacaksın.";
			link.l1 = "Ben öyleyim ve öyle kalacağım. Yakında döneceğim, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway  size yardım etti, Kaptan. Şimdi sözünüzü tutma sırası sizde.";
			link.l1 = "Her şeyi duydun, Longway. Hadi gidelim, kardeşini görelim.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Efendim Kaptanım, Longway’in son bir isteği var: Chang Xing’in kendini açıklamasına izin verin. Kararınızı vermeden önce onu dinleyin.";
			link.l1 = "Ne oldu "+sStr+" onun üzerinde. Ama önce kendini açıklamasına izin vereceğim.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway sizin sözünüze, muhakemenize ve nezaketinize güveniyor.";
			link.l1 = "Dostum, bu kanlı karmaşada ne akla ne de merhamete yer var. Artık buna bir son vermenin vakti geldi.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Efendim Kaptanım...";
				link.l1 = +sStr+" öldü.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Kaptan, hanımefendi "+sStr+", sizi görmek büyük bir zevk. Bu... Chang Xing.";
					link.l1 = "Anladım Longway. Geri çekil. Kız kardeşinle konuşmak için yeterince vaktin oldu. Şimdi o hesap vermeli "+sStr+" Levasseur'un adamlarının onu kaçırmasına yardım ettiğin için.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Geldiniz... Hanımefendi nerede "+sStr+"? O... mu...?";
					link.l1 = "Hayır, Longway. Tanrıya şükür, hayır. Onu gemiye götürdüm. Yoksa şu anda seninle bu konuşmayı bile yapıyor olmazdım. Yine de, kolay ya da hoş olmayacak.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing ve ben başsağlığı diliyoruz...";
			link.l1 = "Chang Xing'den başsağlığı mı?! Aynı şekilde Levasseur adına da başsağlığı dileyebilirsin, Longway! Onun kaçırılmada parmağı olduğunu gayet iyi biliyorsun "+sStr+" diğerleriyle birlikte onun uşakları! Ve şimdi o da yok...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Biz.. Şu anda ne hissettiğinizi anlıyorum, Efendim Kaptanım.";
			link.l1 = "Gerçekten mi?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Anne babamı kaybettim, hatırlarsanız. Eğer hatırlıyorsanız tabii. Ayrıca, işkence edip öldüren Chang Xing değildi "+sStr+". Acını, öfkeni anlıyorum. Ama kız kardeşimin suçu, senin düşündüğün kadar büyük değil. Lütfen, beni dinle.";
			link.l1 = "Hatırlıyorum. Hikayeni dinleyeceğim. Ama çabuk ol! Ve bil ki, böyle bir şeyi cezasız bırakamam!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "O zaman her şeyi tekrar anlatmam iyi olur, Monsieur de Maure. Bizim Tu'nun Fransızcası o kadar kötü ki, az kalsın ona saldıracaktınız.";
			link.l1 = "Ağzını kapalı tutmalıydın. Longway'e saldırmayacaktım, ama sen... Onun ölümünden sorumlu olan sensin.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Buna karşı çıkmak isterdim, ama sanırım istemiyorum. Tu, sizi saygıdeğer ve anlayışlı biri olarak anlattı. Ama gerçekten öyle mi? Konuşmaya başlamamın bir anlamı var mı? Yoksa kararınızı çoktan verdiniz mi?";
			link.l1 = "Birinin aklına girmenin yolunu biliyorsun, madam. Şu anda tartışmaya değmez gerçekten. Ama kendini savunmak istiyorsan... Buyur, dinliyorum. Longway'in hatırı için, seni dinleyeceğim.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Her şeyi açıklayabilir, Efendim Kaptanım... Düşündüğünüz gibi değil... Gerçekten değil...";
			link.l1 = "O zaman açıkla. Ama bana değil. "+sStr+" . Gözlerinin içine bak. Morluklarına ve yaralarına bak. Ve ona öyle olmadığını söyle.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Xing adına özür dilerim, Kaptan...";
			link.l1 = "Yüzündeki alaycı sırıtışa bakılırsa, bunu boşuna yapıyorsun. O, özrünü hak etmiyor.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Ona fazla sert davranıyorsunuz, Monsieur de Maure. Gerçi muhtemelen ona hep böyle davranmaya alışmışsınızdır – sıradan sarı tenli bir işçiymiş gibi.";
			link.l1 = "Longway'i bana karşı çevirmeye mi çalışıyorsun? Boşuna uğraşıyorsun. Ona her zaman saygıyla davrandım ve o da bunu biliyor. Önemli olan tek şey bu. Farkındayım, artık elinde sadece oyunlar kaldı.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ne yapmak istiyorsun? Zavallı Tu'yu ailesinden mi ayıracaksın? Onları on yıl sonra nihayet bulmuşken?";
			link.l1 = "Kan her zaman aile yapmaz. Ama ne yapmamızı öneriyorsunuz? Yaptıklarınıza neyi bırakmamızı "+sStr+" cezasız mı kalacak? Ve Longway, başka kızları hiç düşünmeden satan bir kadını arada bir ziyaret mi edecek?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Öncelikle, dinle. Ondan farklı olarak, az önce ona anlattığım hikayemi kusursuz Fransızcayla tekrar anlatabilirim. Kendi hikayemi. Gözlerinin içine bakarak, hatta onun gözlerinin içine bakarak. Ve bunu, artık bıkkınlık getiren o aksan olmadan yapabilirim. Sonuçta, kaybedecek neyimiz kaldı ki?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Neden olmasın, Efendim Kaptanım...?";
			link.l1 = "Bunu gerçekten sormana gerek var mı? O, kaçırılma olayına karışmıştı "+sStr+", değil miydi?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Ben... içtenlikle özür dilerim. On yıl önce kız kardeşimi kurtaramadığım, onu tüm bunlardan koruyamadığım için bu benim de suçum.";
			link.l1 = "En ufak bir pişmanlık duymayanlar için özür dilememelisin, Longway. Burada işin bitti mi? Şimdi onunla konuşma sırası bende.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Efendim Kaptanım, bekleyin! Chang Xing, Levasseur gibi değil. En azından tamamen değil. Bana bu on yıl boyunca yaşadıklarını anlatacak. Size de anlatmama izin verin.";
			link.l1 = "Pekala, Longway. Dinliyorum seni. Anlatacakların çok şeyi değiştirebilir.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Eğer bunu sen anlatırsan, hepimizin başı ağrır. İzin ver, Tu. Charles de Maure, sanırım?";
			link.l1 = "Doğru. Ve sen Belle Etoile’sin, diğer adınla Chang Xing. Sevgilimi kaçırmada Thibaut ve Martene’yle birlikte rol oynadın. Bunu söylediğimde gülümsüyorsun. Güzel anılar mı?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "Bunu inkar etmek aptalca. Ama şimdi ne olacak? Beni kardeşimin önünde işkenceye mi çekeceksin? Yoksa ona yardım etmesini mi isteyeceksin? Ya da beni öldürecek misin? Ona bunu gerçekten yapar mısın?";
			link.l1 = "Dediğim gibi, şu anda her ne kadar başka bir şey yapmak istesem de, hâlâ seninle konuşuyorum. Zorlamaya kalkma. Ona daha önce ne söylediysen bana da söyle. Sonra hepimiz nereye varacağız, görürüz.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Hâlâ Chang Xing'in böyle birine dönüşeceğine inanamıyorum...";
				link.l1 = "İnsanlar değişir, Longway. Herkes kırılabilir ya da içlerindeki son iyilik ve inanç damlaları da silinip yok olabilir.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway hâlâ inanamıyor, kız kardeşimin böyle bir şeye dönüştüğüne... Neden... neden? Keşke o gün evde olsaydım...";
				link.l1 = "Kendini keşke'lerle hırpalama. Hem, bunca yıl boş durmadın ki – her şeyi düzeltmek için gerçekten çok uğraştın.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Sanırım bu böyle, Efendim Kaptanım.";
			link.l1 = "Buradan gidelim. Hâlâ onun ardında bıraktığı karmaşayı temizlememiz ve kurtarmamız gerekenler var "+sStr+" en kısa zamanda.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Evet. Acele etmeliyiz - zaten benim yüzümden çok fazla gecikti.";
			link.l1 = "Bu senin suçun değil, Longway. Hadi acele edelim!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Doğru. Desteğiniz için teşekkür ederim, Efendim Kaptanım.";
			link.l1 = "Boşver. O senin bu kadar çabana hiç layık değildi zaten – seni arayan o olmadı, arayabilecekken bile. Senin yıldızın çoktan sönmüş, o da uzun zaman önce ailenden çıkmış. Artık biz senin aileniz, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Evet... Öylesiniz. Ve ben de bunca zaman bunu göremeyecek kadar kördüm.";
			link.l1 = "Geç olsun, güç olmasın. Şimdi eve dönelim - gemimiz bizi bekliyor.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Tamam. Bunu ne kadar çok istediğimi asla bilemezsin.";
			link.l1 = "Bence biliyorum. Nasıl hissediyorsun, Mary? Kan dökülmesini istemememin sebebi, her zamanki gibi kılıcını sıkıca tutup tutamayacağından emin olmamam. Ben diğerleriyle uğraşırken biri üstünlük sağlayabilirdi.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Beni hafife alıyorsun. Ayrıca, öfke müthiş bir ilaçtır. Beni kurtarmaya koşacağından hiç şüphem yoktu – her zamanki gibi, di mi? Biliyor musun Charles... Bana Kızıl Tılsımım diyorsun ya, peki ya sen de benim tılsımım olsan? Birlikteyken hep olağanüstü bir şey oluyor.";
			link.l1 = "Ben senin tılsımın mıyım? Neden olmasın, bu fikri sevdim.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Bak işte, gülüyorsun bile! Şimdi bu iğrenç yerden çıkalım - hadi acele et, çabuk çabuk, di mi.";
			link.l1 = "Eh-heh, bu karmaşa beni fena vurdu. Keşke başka bir şekilde sonlanabilseydi.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Ben öyle düşünmüyorum. Onu kurtarmak imkansızdı, Charles. Ve Longway'i de beraberinde sürükledi. Longway kendi yolunu seçti, bize de başka bir yol bırakmadı. Bugün yardım ettiğimiz onca insanı düşün.";
			link.l1 = "Yine sana karşı çıkacak bir şeyim yok, Mary. Hem bu sefer, istemiyorum da. Gel, Kızıl Tılsımım...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Orada ne oldu, monsieur? Küfürler ve bağırışlar duyduk. Ama bitene kadar yardım çağırmaya cesaret edemedik.";
				link.l1 = "Ve haklısınız. Ev sahibiniz öldü. Artık gitmekte özgürsünüz. Yerinizde olsam, işletmenin kasasını toplar, aranızda paylaştırır ve mümkün olan en kısa sürede adadan kaçardım. Sizin onurlu hanımefendiler olduğunuzu biliyorum, sıradan fahişeler değil, bu berbat yerin ötesinde de bir geleceğiniz olacak.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ah, siz misiniz, monsieur. Ev sahibesi ne zaman aşağı inecek, biliyor musunuz?";
				link.l1 = "Yakında değil. Ve yerinizde olsam kapıdan uzak dururdum. Bu akşam hakkında onunla asla konuşmayın - hiçbir şey anlatmaz, ve meraklı kediler bir anda canından olur. Görünen o ki hanımefendiniz sırlarına burnunu sokanlardan hiç hoşlanmıyor.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Onu sen mi öldürdün?!";
			link.l1 = "Yaptım. Ve eğer oyalanırsanız ya da gardiyanları çağırmaya kalkarsanız, bu sizin en büyük hatanız olur. O asla sizin koruyucu azizeniz olmadı – size ne kadar ipek ve eğitim vermiş olursa olsun, burada hapis tutuluyordunuz, o kimi gösterirse ona teslim olmaya zorlandınız. Buradan kurtulmanız için hepinize bol şans diliyorum. Hoşça kalın, hanımlar.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Gerçekten iyi mi? İçeri girebilir miyiz? Muhafızları çağırmamız gerekiyor mu?";
			link.l1 = "O asla iyi olmayacak. İstersen kendisine sorabilirsin... ama kendi riskinle. Hâlâ kardeşiyle konuşuyor. Ve sanmıyorum ki rahatsız edilmekten memnun kalacaklar.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Anladım... Peki, yine de bir ara uğrayın bize, monsieur.";
			link.l1 = "Asla. Elveda, hanımlar.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Dur! Mademoiselle Etoile'ın yerinden çığlıklar ve kavga sesleri geldiği bildirildi. Muhafız, bununla bir alakanız olduğunu düşünüyor. Silahlarınızı bırakın ve bizimle gelin, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Doğru, ama kavgayı biz başlatmadık, biz bitirdik. Tutulan haydutlar, ödemeleri geciktikleri için isyan edip Madame Etoile'a saldırdılar, onu soymak için. Paralı askerlere güven olur mu, ha? Biz galip geldik, ama maalesef o hayatta kalamadı.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Bugün hayatımın aşkını kaybettim, o yüzden izin verin geçeyim, memur bey.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Bunun sadece sizin sözünüzle yetinemeyeceğimizi anlıyorsunuz, değil mi? Sizi alıkoymamız gerekecek. Ayrıca kadın çalışanlardan da şahitlere ihtiyacınız olacak. Bakalım onlar ne diyecek.";
			link.l1 = "Sevdiğim kişi ağır yaralı. Ben de ölü gibi yorgunum. Bizi bırakıp gitmemize izin veremez misin, lütfen?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Bunu en kısa sürede halletmeye çalışacağız. Şimdi bizi takip edin.";
			link.l1 = "Cehenneme git...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Başınız sağ olsun, monsieur. Henüz bir subay değilim ama... neyse, önemli değil. Bizimle gelir misiniz ve orada ne olduğunu anlatır mısınız?";
			link.l1 = "Sana anlatayım. Genelev zarar ediyordu, kasada paralık kalmamıştı ve onu koruyan paralı askerlerin ödemesi yapılamıyordu. Onlar da kalan ne varsa almaya karar verdiler, ben de o sırada oradaydım. Madame Etoile ile birlikte onlara karşı savaştık ama o aldığı yaralardan öldü. Şimdi, artık geçmeme izin ver.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Çok isterdim, ama doldurmam gereken bir sürü evrak var. Bir de orada çalışan hanımlarla görüşmem lazım. Doğruyu söylüyor olsanız bile, en az bir gün kasabada kalmanız gerekecek, monsieur.";
			link.l1 = "Cehenneme git...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway'ın sizin için bir şeyi var, Efendim Kaptanım.";
			link.l1 = "Ne kadar güzel ve tuhaf. Böyle bir şeyi hiç görmemiştim. Bu nedir?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "Bu, memleketimin Kaptan tılsımıdır. Ve, Longway artık bir Kaptan olmadığı için, onu size veriyorum.";
			link.l1 = "Teşekkür ederim, Longway. Van der Vink’in ölümüyle, intikamını almak istediğin herkesten öcünü aldın. Her şeyin böyle sonuçlanmasına sevindim.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Keşke Xing'i tekrar iyi bir insan olmaya ikna edebilsem...";
			link.l1 = "Artık kimseyi dinlemek istemezdi, kardeşini bile. Elinden gelenin en iyisini yaptın. Hepimiz yaptık.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Evet... Çok teşekkür ederim, Efendim Kaptanım. Longway artık özgür, yeniden bir yuvası ve dostları var.";
			link.l1 = "Rica ederim, dostum. Şimdi, benimle birlikte kardeşimi görmeye gelmek ister misin? Ah, ne ironik!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			ReturnOfficer_Longway();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Yine buradayız François. Görüyorum ki hayat seni epey yıpratmış, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, seni açgözlü herif... Kasaların altınla dolup taşıyor, neredeyse boğulacaksın, ama hâlâ doymak bilmiyorsun?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Seninle de paylaşacağım, François. Sana yetecek kadar var, bana güven.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Ne... ne demek istiyorsun?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Genel Vali, siz şimdi...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, dostum, işini yaptın ve harika yaptın! Bu adama ne olacağı seni ilgilendirmemeli... Ama yine de bilmen faydalı olur, Kaptan, olur da bir gün o parlak kafana aptalca fikirler gelirse diye. Ortak dostumuzu, tabiri caizse, kötü bir hazımsızlık bekliyor. Duyduğuma göre altın mideye iyi gelmezmiş... Umarım daha fazla açıklamama gerek yoktur.";
			link.l1 = "Hayır, Genel Vali.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Monsieur François'dan farklı olarak, senin önünde parlak bir gelecek var Charles. Çocuklar, şu domuzu hapse atın!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Ellerinizi çekin, alçaklar! Memnun musun, de Maure?! Defolun! Hepimiz aynı cehennem tavasında yanacağız, birlikte!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Pekala, efendim. Hanımefendiyi inceledim "+sStr+"...";
			link.l1 = "Ne kadar kötü, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Endişelenecek bir şey yok, Kaptanım. Mary ağır yaralandı tabii ki, ama genel olarak her şey yoluna girecek. Birkaç gün yatakta kalmalı, sanırım iki hafta içinde tekrar aramıza katılır.";
					link.l1 = "Anladım. Teşekkürler, Raymond. Gidebilirsin.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary fena dayak yedi, Kaptan. Morluklar, kesikler... ve tabii ki yaşadığı şok - ama bunu belli etmemeye çalışıyor.";
					link.l1 = "Her zamanki gibi güçlü görünmeye çalışıyor. Ama sanırım artık yatakta dinlenmesinin daha iyi olacağını fark etti. Peki, ne kadar sürecek bu?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Profesyonel bir asker bile onun yaşadıklarından sağ çıkmakta zorlanırdı, Kaptan. Burkulmalar, incinmeler, morluklar - o alçakların kemiklerini kırmamış olmalarına şanslıyız. Ama tendonları zarar görmüş, bu yüzden en az bir ay boyunca kılıç kullanamayacak.";
					link.l1 = "Bıçağın canı cehenneme. Ne zaman ayaklarının üstünde durabilecek?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Endişelenmeyin, Kaptan. Hellen yaralandı, ama durumu ciddi değil. Şimdilik yatakta kalması gerekecek, ama bence birkaç hafta içinde tamamen iyileşecek.";
					link.l1 = "Anladım. Teşekkürler, Raymond. Gidebilirsin.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "O, ağır bir darbe aldı, kaptan. Ve fiziksel yaralar sadece teşhisin bir parçası... O korkunç yerde olmak, ona Arbutus'ta yaşadığı kâbusu hatırlattı.";
					link.l1 = "Elbette... lanet olsun! Ne zaman kendine gelecek?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen bıçak sırtında yürüdü, Kaptanım. Bunca şeyden sonra hayatta kalmasına şaşırdım. İç kanama ya da kırık yok, ama burkulma ve incinme çok.";
					link.l1 = "Zavallı kız. İyileşmesi ne kadar sürecek?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "En az bir hafta, efendim. Tavsiyelerime uyarsa, yaklaşık bir ay içinde tekrar ayağa kalkar.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "İki haftadan önce olmaz, efendim. Ondan sonra, güverteye kısa yürüyüşlere çıkmasına izin vereceğim. Tamamen iyileşmesi en az iki ay sürecek.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Onu en az bir hafta rahatsız etmeyin, size söyleyeyim efendim. Tamamen iyileşmesi yaklaşık bir ay sürecek.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Anladım. Teşekkürler, Raymond. Gidebilirsin.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Uzun süre yattıktan sonra kendi başıma ayakta durmak sandığımdan daha zormuş, di mi!";
				link.l1 = "Belki de yatak istirahatini bu kadar ani bırakmamalısın, sevgilim.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ah, başım...";
				link.l1 = "Helen! Biraz erken kalkmadın mı? Ayakta zor duruyorsun!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Bu lanet yatağa bir daha yatmaktansa yakmayı tercih ederim - en azından baştan kıça kadar yürüyüp geri dönene kadar!";
				link.l1 = "Güzel, rahat bir yatak. Gemi de fena değil. O yüzden seni durdurmayacağım. Ama aptalca bir şey yapmadığından emin olmak için orada olacağım.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "İyiyim, Kaptanım, ama tam anlamıyla değil. Henüz kılıç sallamaya hazır değilim, fakat bu yataktan tüm ruhumla nefret ediyorum.";
				link.l1 = "Eh, güvertede kısa bir yürüyüş sana zarar vermez herhalde. Ama halatlara yaklaşmayı aklından bile geçirme!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, beni tamamen unuttuğunu düşünmüyor musun? En son ne zaman birlikte yattığımızı hatırlat bana, di mi!";
				link.l1 = "Ondan önce... Bundan bahsetmeyelim, olur mu Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Benim kaptanım, bir kadın olarak artık ilgini çekmiyor muyum?";
				link.l1 = "Bu beklenmedik oldu, Helen. Genellikle bu konuyu açan ben olurum... ama senin hazır olup olmadığından emin değildim, o olaydan sonra...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "O zaman en azından benden bahset, di mi. Yoksa o iki alçak beni dövdükten sonra sana tatsız mı geldim?";
				link.l1 = "Şimdiye kadar duyduğum en saçma şey bu. Sadece hazır olana kadar seni rahatsız etmek istemedim. Ve madem hazırsın...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Sorun yok Charles, gerçekten. Sadece bunu düşünmemeye çalışıyorum. Hem, beni en kötüsünden sen kurtardın. O yüzden artık konuşmayı bırakalım ve... biraz sohbet edelim.";
				link.l1 = "Bu gerçekten harika bir fikir, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, bunu istemiyorum, bunu talep ediyorum, di mi!";
				link.l1 = "Sana karşı gelmeye cesaret edemem...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, konuşmamız lazım, di mi.";
				link.l1 = "Bir sorun mu var, Mary? Oldukça endişeli görünüyorsun, bu da genelde iyiye işaret değildir.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kaptanım, size söylemem gereken bir şey var.";
				link.l1 = "Öyle mi, Helen? Dinliyorum.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "İşte mesele bu! Görevime subay olarak dönmeye hazır olmam iyi bir şey değil mi?";
				link.l1 = "Yani bu kadar. Eğer kendini yeterince güçlü hissediyorsan, bu sadece iyi değil, harika.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mürettebatın bana sanki güçsüz yaşlı bir kadınmışım gibi bakmasından bıktım. Dümene geri dönmek ve kollarımı bir kılıçla çalışarak açmak istiyorum...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Eğer kendini hazır hissediyorsan, itiraz etmem, sevgilim. Eşyalarını getiririm. Ve dümeni de seve seve sana bırakırım. Ama bir kavgada dikkatli ol, olur mu?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Köprüde seni özledik, Helen. Ve şu kılıç... Sanırım artık onu geri almanın zamanı geldi.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Elbette, Benim kaptanım, ne derseniz o olur.";
			link.l1 = "İyi.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Harika, tamam! Kılıçla çalışmak için sabırsızlanıyorum...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Bunu duyduğuma sevindim, Mary. Ama hemen olayların içine atlama... Gerçi, kime söylüyorum ki?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Kılıcın tekrar kınına dönmesini görmek seni mutlu edecek sanırım...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ben... Ben ne diyeceğimi bilmiyorum, Charles. Bu pala'nın benim için ne kadar değerli olduğunu ancak şimdi fark ettim...";
				link.l1 = "Bunu çok uzun zaman önce biliyordum, bu yüzden seni beklerken sapasağlam kaldı.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Benim narvalım, di mi!!! Charles, onu kurtardın! Sadece mutlu değilim, heyecandan yerimde duramıyorum! Teşekkür ederim, teşekkür ederim! Martin'in gemisinde kaldı diye çok korkmuştum...";
				link.l1 = "Bu kılıç senin eline yakışır, Kızıl Tılsımım. Bir daha kaybetmeyeceğine güveniyorum... Neyse, kavuşmanıza engel olmayacağım, ha-ha!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Teşekkür ederim, Charles. Biliyor musun, sanırım bu yüzden seni seviyorum...";
				link.l1 = "Kayıp şeyleri geri getirmek için mi? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Gülüyorsun, ama ben ciddiyim.";
			link.l1 = "Biliyorum, Helen. Ben de seni seviyorum, ama hâlâ nedenini tam olarak bilmiyorum.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Belki de bu palayı henüz senin üzerinde kullanmadığım içindir.";
			link.l1 = "Ben kendimi bundan kurtaracağım, sandallara gidiyorum. Orada seni bekleyeceğim, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 
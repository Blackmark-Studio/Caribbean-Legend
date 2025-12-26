void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bu bir hata. Geliştiricilere haber verin.";
			link.l1 = "Yapacağım!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Merhaba, solgun yüzlü. Büyük bir kano kaptanı olduğunu görüyorum. Ben Kanauri. Cayman'ın reisi, güçlü Arawak kabilesinin lideriyim. Seninle konuşmak istiyorum.";
			link.l1 = "Dinliyorum, şef. Seni bana hangi dertler getirdi?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Benden ne istiyorsun, seni pis kırmızı tenli maymun? Ormandan geldiğin yere dön ve isteklerinle beni rahatsız etme.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! Beyaz kaptana kibar olmayı öğretmediler mi? Sana bir teklif sundum. Bir sürü wampum kazanabilirdin ama şimdi gidiyorum. Elveda, soluk yüz.";
			link.l1 = "Yürü git, kaybol...";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "Beyaz kardeş, baykuş gibi sezgili, yılan gibi kurnaz. Kızılderiliye bela geliyor. Beyaz adamların büyük-büyük kayığı köyüme geldi. Birçok Cayman’ı, halkımı aldılar, kayıklarına koyup Hepsinin Anası Sular’a götürdüler...";
			link.l1 = "Bekle... yani diyorsun ki, senin halkını bir gemiden gelen beyaz adamlar köleleştirdi?";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Doğru söylüyorsun, beyaz kardeş. O solgun yüzlülerin sana dost olmadığını biliyorum. Bu acımasız beyaz adamlar, İspanyol kabilesinden. Halkımı alıyorlar. Ama onları bulurum. İspanyollar, Kızılderilileri gün doğumundan gün batımına kadar çalıştırıyor, Suların Anası'nda derinlere daldırıyor, tanrıların gözyaşlarıyla dolu kabukları bulduruyor.";
			link.l1 = "İnci dalıcılığı... Bu gerçekten acımasız bir iş.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Doğru söylüyorsun, beyaz kardeş. O insanların sana dost olmadığını biliyorum. Onlar İngiliz kabilesinden. Benim halkımı alıyorlar. Ama onları bulurum. İngilizler, Kızılderilileri gün doğumundan gün batımına kadar çalıştırıyor, Suların Anası'nda derinlere daldırıyor, tanrıların gözyaşlarıyla dolu kabuklar bulduruyorlar.";
			link.l1 = "İnci dalıcılığı... Bu gerçekten zorlu bir iş.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Hintler kölelikten hastalanıp ölüyor. Beyaz adamların Hintlilere acıması yok. Kamçı ve tabanca, beyaz adamın Hintlilere uyguladığı tek yasa. Ben yaşlandım. Savaşacak adamım kalmadı. Cayman Arawakları barışçıl bir halktır, barış pipo­sunu biz icat ettik. Sana yalvarıyorum, beyaz kardeş, kamçını ve tabancanı kötü beyazlara karşı çek, Arawakları kurtar.";
			link.l1 = "Benden savaş ilan etmemi mi istiyorsun? Şunu anlamalısın, şef, kaynaklarım sınırlı.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "Savaş yoluna gitme. Özgür Kızılderili. Benim halkım. Size kano içinde sahip olduğumuz tüm tanrı gözyaşlarını veririz. Kötü beyaz adamı öldür, Kızılderili'ye yardım et, tanrı gözyaşlarını al, onları çokça wampum karşılığında sat. Bir yığın wampum";
			link.l1 = "Ah, şimdi anladım. Hayır, Canauri, sana yardımcı olamam. Şu anda bunu yapamam - gemim tamire muhtaç, elimde hiç erzak kalmadı...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "Bu durumda, memnuniyetle yardımcı olurum. Detayları konuşalım. Adamların nerede? Onları zaten bulduğunu söylemiştin...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u! Bekleyebilirim, beyaz kardeş... Bir ay daha bu limanda olacağım, halkım için bir koruyucu arayacağım. Hazır olduğunda beni burada bulursun.";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "Geri mi geldin, beyaz kardeş? Kötü adamlara ceza vermeme ve Hintliyi kurtarmama yardım edecek misin?";
			link.l1 = "Hazır olduğum kadar hazırım.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Hâlâ hazırlanmam gerekiyor.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Burada olacağım, beyaz kardeş.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Teklifimi kabul ettiğine çok sevindim, beyaz kardeş!";
			link.l1 = "Detayları konuşalım Canauri. Adamların nerede? Onları çoktan bulduğunu söylemiştin...";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "Onlar Carupano Koyu'nda, İspanyol kampı Cumana'nın yakınında kamp kurmuşlar. Her gün teknelerle denize açılıyorlar, suya dalıyorlar, derinlere, daha da derinlere...";
				link.l1 = "Anladım. Ve onlar dalarken İspanyollar başlarında mı bekliyor?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "Onlar, İngiliz kampı Blueweld’in yakınındaki Cape Perlas’ta kamp kuruyorlar. Her gün denize açılıp sandallarla derinlere, daha da derinlere dalıyorlar...";
				link.l1 = "Anladım. Ve tabii ki, İngilizler de onları gözetliyor, değil mi?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Evet, ateşli sopaları ve büyük bıçakları olan iki büyük soluk yüzlü kano geldi. Kıyıdaki kamp da korunuyor - Kızılderili kaçamaz.";
			link.l1 = "Ne tür gemiler? Tarif edebilir misin? Ne kadar büyüktüler? Ne tür yelkenleri vardı?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Bu kano büyük, ama Canauri daha büyüğünü gördü. Ön yelken çok, çok eğik, böylece üç tarafı böyle oluyor. (Toprağa üç tane latin yelkeni ve bir yamuk yelken çiziyor) Üstü dar, altı geniş.";
			link.l1 = "Sesinden ve görünüşünden bir şalopa benziyor...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri o kelimeyi bilmiyor. Solgun yüz, başka bir kano görürse çok dikkatli olmalı – Hintliyi karaya çıkarıyorlar ve diğer kano uzaklaşana kadar bekliyorlar.";
			link.l1 = "Temkinli herifler... onlara nasıl yaklaşabilirim?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Eğer soluk yüzlü kardeş küçük bir kano alırsa, kıyıya sessizce yaklaşabilir. Yolu ben göstereceğim. Ama sadece bir küçük kano getir, yoksa soluk yüzlü köpek görür ve Hintliyi kayıktan kovup ormana sürer...";
			link.l1 = "Anladım. Bu iş için bir lugger ya da bir sloop lazım olacak. Güzel. Bir sloop ile iki şunere karşı... Tanrım... ve ben de bunun kolay olacağını sanmıştım!";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Gidelim mi, beyaz kardeş? Bir aydan az vaktimiz kaldı.";
			link.l1 = "Evet. Gemime çık, şef. Zaman kaybetmeyelim!";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "Teşekkürler, beyaz kardeş! Cayman Arawak kabilesini kurtardın! Sana büyük bir borcumuz var. Yol artık soluk yüzlü köpeklerden temizlendi, Kızılderililer ormanda özgürce dolaşabilir. Tanrıların teknelerde bıraktığı tüm gözyaşlarını sana veriyoruz.";
			link.l1 = "Pekala, görelim neler yapabileceksin...";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("Tanrıların gözyaşlarının sana ait olmasına sevindim, Arawakların kardeşi!"," Kızılderili, teşekkür ederim, cesur beyaz yüz! ","Al bizim avımızı, beyaz kardeş!");
			link.l1 = LinkRandPhrase("Sana yardım etmekten memnuniyet duyarım!","Teşekkürler, kızıl derili kardeşim!","Harika!");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Canauri sana tekrar teşekkür ediyor, solgun yüzlü kardeşim! Tüm kanoları ve Kızılderilileri kurtardın! Canauri için her kanoyu kurtarmak çok önemli, çünkü kötü solgun yüzlülerin köleliğe götürdüğü Canauri'nin torununu da kurtardın. Torunum çocukken yüzmeyi çok severdi, Canauri ona boğulmasın diye bu tılsımlı muskayı vermişti. Şimdi torunum artık yüzmek istemiyor ve muskayı bana verdi ki ben de onu sana vereyim, solgun yüzlü kardeşim. Umarım tanrıların gözyaşları ve bu hediye, bir Arawak'ın hayatı için yeterli bir ödül olur. Ve şimdi veda ediyoruz - artık köyümüze dönme vakti geldi.";
				link.l1 = "İyi şanslar, Cunauri! Torununun hayatta kalmasına çok sevindim! Bu kötülüğün bir daha başına gelmemesi için dua ediyorum!";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri sana tekrar teşekkür ediyor, solgun yüzlü kardeşim! Umarım tanrıların gözyaşları, Kızılderililerin hayatları için yeterli bir ödül olur. Şimdi hoşça kal, biz kendi köyümüze dönüyoruz.";
				link.l1 = "İyi şanslar, Cunauri! Bir daha asla köleliğe düşme!";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

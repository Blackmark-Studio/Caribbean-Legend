// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Sen hiç, tesadüfen, Kaptan Edgardo Sotta ile karşılaştın mı? Onun hakkında bize bir şey söyleyebilir misin? Tanışmaya değer biri gibi görünüyor.";
					link.l1.go = "Sotta1";
					link.l2 = "Rüzgâr Torbası'nın idamını izlemeye gitmeyecek misin?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Söylesene, bugünlerin kahramanı Kaptan Edgardo Sotta'yı gördün mü? Maalesef ben kaçırdım. Nasıl biri? Şuna inanamıyorum, bir tüccar o meşhur Geveze Matt'i yakalamış!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Bütün kasabanın Lutter'ın yakalanışını kutladığını görüyorum, denize hiç açılmayanlar bile."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Yaklaşık bir buçuk ay önce, Jerome Sauvernier adında biri Belize'ye geldi. 'Cam Göz' meyhanesinde bir kavgada yaralandı ama hayatta kaldı. Onu nerede bulabileceğimi söyleyebilir misiniz?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Bir buçuk ay kadar önce, Belize'de bir beyefendi ortaya çıktı. Adı Jerome Sauvernier'di. Başka bir adamı arıyordu – yani kasaba halkıyla konuşmuş olmalı. Sonra bir meyhanede çıkan kavgada yaralandı, ama neyse ki hayatta kaldı. Bana onu nerede bulabileceğimi söyleyebilir misin?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Yaklaşık iki ay önce Belize'ye gelen bir adamı arıyorum. Adı Jerome Sauvernier. Belirli bir beyefendiyi arıyordu, sanırım bu konuda kasaba halkıyla konuşmuştur...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence gizli serviste mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O halde hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şey bilmiyorum.";

            link.l1 = "Sen tam bir şaşkınsın! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı, o zaman?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Onunla konuşma fırsatım olmadı, ama gemisini gördüm - ağır bir kalyondu. Bu sularda tek başına seyretmek tehlikelidir, ama Sotta bunu korumasız da başarabiliyor.";
			link.l1 = "Muhtemelen her altın paranın peşinden koşup, elinden geldiğince masrafları kısıyor. Neyse, sizi tutmayayım. İyi günler.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "İnanması güç, değil mi! Ama duyduğunuz her şeye inanmayın, efendim. Onu gördüm, sizi gördüğüm kadar net. Lutter'ı yakalaması iyi oldu ama bu tüccar numarası da neyin nesi? Davranışları tam bir asker gibi. Hep anlarım – bir akrabam yıllarca askerlik yaptı.";
			link.l1 = "İlginç. Herkesin sırları vardır sonuçta. Ben artık gideyim. Paylaştıkların için teşekkürler.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Adamı zaten gördüm. Yıllarca tüccarlarımızı dehşete düşüren o korsanın aynı kişi olduğuna inanmak zor. Nasıl oldu da kendi komutasını alabildi ki? Onu askerler eşliğinde gördüm – bağırıyor, ağlıyor, gülüyordu. Tam bir deli.";
			link.l1 = "Belki de yenilgi ve yaklaşan ölümü gerçeği onun için fazla ağır geldi. Ama artık önemi yok. Hoşça kal!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Evet, ben de kutluyorum – birçok hemşehrim onun elinde can verdi. Şanssız olanlar babalarını, kardeşlerini, oğullarını kaybetti – ne demek istediğimi anlıyorsun. O barbarlık fazlasıyla uzun sürdü! Bana sorarsan, Matt son yılların en şanslı korsanlarından biriydi.";
			link.l1 = "Şans er ya da geç tükenir. Görüşürüz.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Böyle bir adamı tanımıyorum, efendim. Meyhanede kavga çıkması neredeyse her gün olur, kim yaralandıysa hepsini hatırlamak da kimsenin işine gelmez.";
    		link.l1 = "Anladım, teşekkür ederim. Her şey gönlünüzce olsun.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sauvernier mi? Bir Fransız... Evet, öyle biri vardı. Benden yardım istemeye geldi, ama ona yapabileceğim bir şey yoktu. O günden beri kendisini görmedim, affedin.";
    		link.l1 = "Teşekkür ederim. O halde, etrafta sormaya devam edeceğim.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Bay Jerome! Tabii, tabii, onu hatırlıyorum. Bir meyhanede çıkan kavgada yaralandı. O zamandan beri neredeyse hiç evinden çıkmıyor, bacağındaki yarayla ilgileniyor.";
			link.l1 = "Ve bu ev nerede?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "Hemen burada, liman idaresinin yanında, kırmızı çatılı ev. Onu orada bulacaksınız.";
    		link.l1 = "Teşekkür ederim, bana çok yardımcı oldunuz! Size her şeyin en iyisini dilerim!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

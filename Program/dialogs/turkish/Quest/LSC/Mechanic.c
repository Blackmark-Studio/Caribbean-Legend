// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler, efendim. Sizi daha önce hiç görmedim. Yeni mi geldiniz? Bu platforma ilk kez mi uğruyorsunuz?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" .   Ben de yeniyim burada, sadece etrafa bakınıyor ve insanları tanımaya çalışıyorum... ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Dinle, "+pchar.name+", eğer beni oyalamaya devam edersen, tamiratı asla bitiremeyeceğim.";
					link.l1 = "Evet, evet, onu hatırlıyorum. Sizi rahatsız ettiğim için üzgünüm!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Şuna bak hele! Boğulan adam öteki dünyadan geri döndü! Söylesene, nasıl başardın böyle bir numarayı? Senin için cenaze düzenlediler, yokluğunda gömdüler seni, haberin yoksa söyleyeyim...";
					link.l1 = "Ne yazık ki, henüz ölecek değilim. Hilesi basit – sadece Kukulcan'ın idolüne en alttan dokundum. Beni Dominika'ya, doğrudan Karayip köyüne ışınladı...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, sana bir iş teklifiyle geldim. Hem de çok önemli bir teklifle. Ole Christiansen bana senden bahsetti. Ona ayrıca Beyaz Çocuk da derler.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, sana yeterince 'gümüş' getirdim. Tam istediğin gibi: senin bir adamın ve fazladan on parça daha. Al, işte burada.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Yine ben, Henrik. Takımın nasıl? Onarabilmeyi başardın mı?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "İstediğin kadar metalim var. Al bakalım.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Günaydın, Henrik. Peki, dalış için elbise hazır mı?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Her şey bitti, sorunlarımı hallettim ve dalmaya hazırım. Ne zaman başlıyoruz?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Merhaba, Henrik. Peki, dalış için elbise hazır mı?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Takımını geri vermek istiyorum.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Söyleyecek ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Sadece nasıl olduğunu merak ettim.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ve ben de Henrik Vedecker'im. Gerçi buradakilerin çoğu beni Mekanikçi olarak tanır, ki bu aslında beni oldukça iyi tanımlıyor.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Sen Henrik Vedecker misin? Tanıştığımıza memnun oldum! Seni arıyordum.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Sen her işten anlayan biri olmalısın, değil mi?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Ah, evet, Narvaller gerçekten yeteneklerimi takdir ediyor. Aletlerim sayesinde dış halkadaki batık gemilerden birçok değerli eşya çıkarabiliyorlar, böylece Amiral Dodson'dan erzak satın alabiliyorlar.\nAslında, bilim ve keşif benim tutkum. Bu yüzden, seninle yeterince vakit geçiremeyebilirim diye şimdiden özür dilerim – deneylerim neredeyse tüm zamanımı alıyor.";
			link.l1 = "Anladım. Size boş yere rahatsızlık vermem, Bay Vedecker, buna emin olabilirsiniz. Sizi tanıdığıma gerçekten çok memnun oldum!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Öyle miydin? Peki neden?";
			link.l1 = "Ole Christiansen senden bahsetti bana. Ona Beyaz Çocuk da derler.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, o komik adam! Evet, evet, onu tanıyorum. Peki, sana ne söyledi?";
			link.l1 = "Biraz aptalca gelebilir ama... yine de soracağım. Ole, bana suyun dibine dalmayı öğretebileceğini söyledi. Eğer bu sadece onun hayal gücüyse, lütfen bana gülme.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "Doğru. Ben de birkaç kez dibe indim. Artık dalmıyorum, çünkü son zamanlarda sığlık dev yengeçlerle dolup taşıyor ve gördüğün gibi, onlarla savaşacak durumda değilim. Ben bir bilim insanıyım, o yaratıklarla baş edemem.\nAyrıca, eskiden dalan iki adam daha vardı, iki Narval, ama onlar da sonunda vazgeçtiler—dış halka gemilerinin ambarlarını yağmalamak, dev yengeçlerin kaynadığı yerlere dalmaktan daha güvenli çıktı.\nŞimdi ekipmanımı nadiren kullanıyorlar, son birkaç aydır dalış yapan olmadı, çünkü dalış elbisesi çatladı...";
			link.l1 = "Gerçekten de en derinlere dalmanı sağlayan bir giysin mi var? Yanlış mı duydum?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Kulakların yerinde, delikanlı. Bu dalış giysisini ben icat edip kendim yaptım. Kalın, iyice ıslatılmış ve tamamen su geçirmez kanvastan, metal parçalardan ve benle Jurgen'in demirhanesinde dövdüğümüz çelik bir miğferden oluşuyor\nAyrıca giysiyi, yengeçlere karşı daha iyi koruma ve ağırlık için metal göğüs plakası, dizlikler, göğüs parçaları ve botlarla güçlendirdim\nBasınçlı hava dolu özel tanklar, yaşam desteği sağlıyor ve su altında bir süre kalabilmeni mümkün kılıyor. Bu giysi benzersiz ve onunla oldukça gurur duyuyorum.";
			link.l1 = "Harika. Ama takımın hasarlı olduğunu söyledin mi?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Ne yazık ki, bu doğru. Zırhın bazı kısımları, esneklik ve ekstra koruma sağlamak için metal plakalarla birleştirilmişti, fakat deniz suyu onlara çok zarar verdi. Yıllar süren kullanımın ardından plakalar paslandı ve su geçirmezlik özelliklerini kaybetti.\nHasarı fark edip kimsenin ölmesini engellemem iyi oldu. Kuru zırhın içinde bile biraz tuz ve su vardı, onlar bile zararlarını çoktan vermişti.";
			link.l1 = "Peki... Ama zırhı tamir edebilirsin! Eski, paslı parçaları yenileriyle değiştirebilirsin... Değil mi?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Ne amaçla? Bir yıl sonra tekrar değiştirmek için mi? Bu işin ne kadar zor olduğunu biliyor musun? Esnek eklemleriyle zırhı bir araya getirmek ve su geçirmez yapmak? En az bir hafta boyunca dinlenmeden çalışmak gerekir.";
			link.l1 = "Ve bu yüzden mi icadını bir kenara atmaya razısın?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Hayır, tabii ki değil. Bir fikrim var. Menteşeleri suya ya da tuza karşı dayanıklı bir metalden yapmam gerek. Ve hangi metalin işime yarayacağını biliyorum...";
			link.l1 = "Peki sorun ne?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = " Sorun şu ki, bu metal çok nadir bulunuyor. Bende sadece bir parça var, ki bu kesinlikle yetmez. En az on parça daha, hatta belki on beş parça lazım.";
			link.l1 = "Ve bu... bahsettiğin metal de ne?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Ah, bu eşsiz bir metal, gerçekten de çoğu kişi tarafından küçümseniyor. Dayanıklılığı yüksek, şekil alabilirliği harika ve dış etkenlere tamamen karşı bağışıklığı var – ne su ne de tuz ona zarar verebilir\nBelki de bu metali daha önce görmüşsündür. Beyazdır, gümüşe benzer, bu yüzden İspanyollar ona 'gümüş' demişler. Ha! Gümüşten yüz kat daha iyi! Hatta altından bile üstün! Bir gün bunu anlayacaklar, ama o gün henüz gelmedi.";
			link.l1 = "Dinle, neden başka tür metaller kullanmıyorsun? Neden o levhaları altından yapmıyorsun? Altının paslandığını ya da bozulduğunu hiç duymadım.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Senin esnek ve canlı bir zihnin var, delikanlı. Bunu bilmek güzel. Ne yazık ki, önerin işe yaramaz. Altın fikri aklıma gelen ilk şeydi. Ama altın, zırhın farklı parçalarını birleştirmek için fazla yumuşak.\nNe yazık ki, sadece platin bu iş için uygun. Parçaları yalnızca platinden yapacağım, yeterince toplamak yıllarımı alsa bile. Ama bu metali daha önce Adalet Adası'nda gördüm – genellikle görünüşü nedeniyle gümüşle karıştırılır.";
			link.l1 = "Hm. Eğer bu... 'gümüş'ten yeterince bulmana yardım edersem, bana dalış kıyafetini ödünç verip suyun altına dalmamı sağlar mısın?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Sormana gerek yok! Tabii ki yaparım. Zaten oraya yengeçler yüzünden dalmayacağımı söyledim, başkası da gitmek istemiyor.";
			link.l1 = "O zaman bana bu metal parçasını göster ki ne aramam gerektiğini anlayabileyim.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "So you are going to search for it? Excellent. Here, take this piece as an example. Look for it among the silver ore and nuggets. It won't be easy to find, but you'll manage. There are small dark spots on silver, but our metal is clear and much harder than silver. The easiest way to test it is by scratching a silver coin on it; if the coin gets damaged, then you've found it.";
			link.l1 = "Pekala. Hemen onu aramaya başlayacağım. Nerede aramam gerektiğiyle ilgili bir önerin var mı?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Maalesef bilmiyorum. Nerede bulacağımı bilsem, kendim yapardım. Ama sana bir tavsiye verebilirim. Rivados gemilerini ara. Oraya gitmem, bu yüzden ellerinde olması çok muhtemel.";
			link.l1 = "Bunu düşüneceğim, Henrik. Umarım şansım yaver gider.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Onarım için en az on parça daha toplaman gerek. Bu kadar yeterli olacak. Bol şans!";
			link.l1 = "Teşekkür ederim. Hoşça kal, Tamirci!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Pekâlâ, göster bakalım... Mükemmel! Aferin, delikanlı! Zor muydu?";
			link.l1 = "Pek sayılmaz...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Pekâlâ, şimdi onarımlara başlayabilirim. Hiç vakit kaybetmeden yarın başlarım. Dalmaya gerçekten heveslisin, değil mi?";
			link.l1 = "Gerçekten de. Sualtını keşfetmeyi çok istiyorum.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Bu çok iyi, çünkü dalışını organize ettiğimizde senden bir iyilik isteyeceğim. Ama bunu sonra konuşuruz. Beş gün sonra yanıma gel, umarım o zamana kadar tamiratı bitirmiş olurum.";
			link.l1 = "Pekâlâ. Sana bol şans dilerim!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Şans kesinlikle gerekir, ama zırhın onarımı esasen ustalık ister. Ayrıca, getirdiğin metallerle levha yapmak için bir günü Jurgen’le fırının başında geçirmem gerekecek.";
			link.l1 = "O zaman sizi rahatsız etmeyeyim. Beş gün sonra görüşürüz. Hoşça kalın!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Evet. Jurgen ve ben harika bir iş çıkardık, getirdiğin parçalar da yeterliydi. Elbise tamir edildi ve hazır. Sadece birkaç test yapmam gerekiyor ama eminim bir sorun yok. Yarın sabah saat 10'da gel — tankları havayla dolduracağım ve istediğini yapabileceksin.";
				link.l1 = "Harika! Dört gözle bekliyorum. Yarın görüşürüz, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Seni hayal kırıklığına uğratmak zorundayım, "+pchar.name+". Tahmin ettiğim gibi, yeterince metal yok. İhtiyacım var "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" tamiri bitirmek için birkaç parçaya daha ihtiyacım var. Yine senden yardım istemek zorundayım.";
				link.l1 = "Pekâlâ, böyle bir gelişme beklemiyordum. Tamam, eksik olan cevherleri bulmaya çalışacağım.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Seni bekleyeceğim. Bu miktarın yeterli olacağından emin olabilirsin. Sadece onları getir, işi bir günde bitiririm.";
			link.l1 = "Umarım öyle olur... Görüşürüz!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Harika! Şimdi dalış kıyafeti onarılacak. Sadece birkaç test yapmam gerekiyor ama eminim ki sorun yok. Yarın sabah saat 10'da gel – tankları havayla dolduracağım ve istediğini yapabileceksin.";
			link.l1 = "Harika! Dört gözle bekliyorum. Yarın görüşürüz, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Evet, dalış giysisi hazır ve hava ile dolu. Dalış yapabilirsin.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Güzel. Ama şimdi dalış yapamam, önce... arkadaşım Nathan Hawk'la ilgili bir meseleyi çözmem gerek. Onu bulamıyorum. Dalgıç giysisi biraz bekleyebilir mi?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Harika! Ne zaman başlıyoruz? Şimdi mi?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Tabii. Bekleyebilir. Arkadaşını bütün bir yıl boyunca mı arayacaksın?";
			link.l1 = "Elbette, yapmam. Belki onu bugün bile bulurum. Onunla işim biter bitmez seni ziyaret edeceğim.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Evet, lütfen. Dalmaya hazır olduğunda gel.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Right now, if you want. But let me give you a little instruction first. You will start your dive from the 'Phoenix' platform; you can get there from the San Gabriel's stern. There is a hoist that will take you to the bottom and back. This is the only way to return\nSo you'd better remember the location of the hoist underwater and don't get lost. The suit's tanks have enough air for twenty minutes of diving. Watch your time or you'll suffocate\nDon't stray too far from the hoist or you won't be able to return in time, and God save you if you leave our shoal – you'll be flattened like a flatfish\nBe careful and watch out for crabs. If you get too close, they'll attack you. Don't take risks if you don't have to; you won't be able to kill a whole pack of them, and running away quickly is not an option down there.";
			link.l1 = "Yengeçlerle ben ilgilenirim. Geri kalan bende. Çok derine dalma, vinçten fazla uzaklaşma ve zamanı unutma. Ne zaman dalabilirim?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Ne zaman istersen, ama sadece sabah 7'den akşam 9'a kadar. Karanlıkta hiçbir şey göremezsin.";
			link.l1 = "Anladım.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "That's just it. Take the suit from the room by the platform. Take it off after a dive and bring it to me. I will fill it with air again. But don't try to dive more than once per day; even 20 minutes of diving and breathing compressed air is bad for your health.";
			link.l1 = "Pekala, o zaman günde bir kereden fazla dalmam.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Anladığına sevindim. Şimdi git, bol şans!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Peki, neden hâlâ buradasın? Kıyafetin seni bekliyor.";
				link.l1 = "Evet, evet. Geliyorum.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Peki, ilk dalış nasıl geçti?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Harika, sonuçlardan memnunum. Batık kalyonda taş bir put buldum. Rivados'un daha önce ona kurbanlar sunduğunu duydum. Söylesene Henrik, bu konuda bana daha fazla bilgi verebilecek birini tanıyor musun?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Pekâlâ. Ben yaptım! Gerçekten ilginçti, ama biraz da heyecan vericiydi.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Tarihimizle ilgileniyor musun? Antonio Betancourt'a git. O burada doğdu. Pluto flütünde yaşıyor. Eğer o bir şey bilmiyorsa, kimse bilmiyordur.";
			link.l1 = "Harika! Ona mutlaka uğrayacağım.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Takımı burada bırak. Yarın ya da başka bir gün gel, içine hava basarım.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Tabii. İşte kıyafetin. Teşekkürler!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Elbette. Hemen getiriyorum!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Peki, ekipmanımı getirdin mi?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Tabii. İşte kıyafetin. Teşekkürler!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Hemen hallederim!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Evet, tabii ki. Elbise test edildi ve hava ile dolduruldu. Taahhüdü yanında getirdin mi? 500.000 peso?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Evet, tabii ki. Al, buyur.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Ah, unuttum! Hemen getiriyorum...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Evet, tabii ki. Elbise test edildi ve hava ile dolduruldu. Her zamanki gibi 'Phoenix' platformunu kontrol et.";
				link.l1 = "O zaman dalacağım. Teşekkürler!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Peki. Yarın ya da daha sonra gel. Takımı hazırlayacağım.";
			link.l1 = "Teşekkürler, Tamirci!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Kostümü geri getirdiğinde paranı geri alacaksın. Adil bir anlaşma.";
			link.l1 = "Teşekkürler, Mekanik! Şimdi dalıyorum.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Bir saniye, lütfen! Hangi heykel? A-ah, şimdi anladım. Güneş batığı 'San-Geronimo'daki o putu kastediyorsun, değil mi? Demek Rivados'un hikâyeleri doğruymuş?";
			link.l1 = "Kesinlikle! Ve hiçbir hikaye yok. Takımadada, birbirine dokunan insanları birinden diğerine, bir daire içinde ışınlayan iki tane daha put olduğunu biliyorum.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Anlıyorum, anlıyorum. Sana güvenmek zorunda kalacağım, ama söylediklerin bilime aykırı saçmalıklar. Işınlanmalar, heykeller... ha! Kim böyle şeyleri düşünebilir ki, bunlar nasıl çalışıyor olabilir?";
			link.l1 = "Bana güven ve burada mantık aramaya çalışma. Yalan söylemiyorum.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Pekâlâ. Ama umarım o meşhur ışınlanman sırasında takımını kaybetmemişsindir?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Elbette, yapmadım. Beni tabiri caizse Karayipler'den kurtardı. İşte burada.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Elbette, yapmadım. Bir bakıma beni Karayiplilerden kurtardı. Ama şimdi yanımda değil.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Öyleyse getir bana, kahretsin! Onu bana geri getirmeden konuşmayacağız, anladın mı?";
			link.l1 = "Sakin ol, Tamirci. Onu sana geri vereceğim!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, gerçekten takımımı getirmişsin! Teşekkür ederim, artık endişelenmeye başlamıştım.";
				link.l1 = "Bunun için endişelenmene gerek yoktu. Sana onu geri getireceğime söz vermiştim.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Takımımı getirmeden buraya hiç gelme.";
				link.l1 = "Pekala, pekala.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Çok iyi. Yenisini yapmayı düşünmeye başlamıştım ama bu en az bir yıllık iş olurdu... Eşyamı sapasağlam geri getirdiğin için iyi bir karar verdiğini gösterdin. Sana bir de hediye vereceğim.";
			link.l1 = "Ciddi misin?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Elbette, öyleyim! Zırhı onarmama yardım ettin ve ilk fırsatta atmadın. Ona iyi baktın ve sonunda bana geri getirdin. Her neyse, işte güzel bir alet çantası. Nasıl kullanılacağını öğren. Onunla birçok faydalı şey yapabilirsin.";
			link.l1 = "Başka ne bekleyebilirdim ki Mekanik'ten! Tabii ki alet çantası! Teşekkür ederim Henrik, gerçekten duygulandım... Böyle bir hediyeyi hak etmemiştim.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne hak ettiğini, neyi hak etmediğini benden iyi kimse bilemez. Al şunu! İşine yarar. Ama kostümü sana tekrar ancak 500.000 peso rehin bırakırsan veririm, çünkü şu putlar sayesinde sürekli bir yerlere ışınlanma huyun var.";
			link.l1 = "Vay canına! Anladım... tedbirli olmak lazım...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Tabii. Peki ya bir gün onunla kaçarsan? O zaman para benim tazminatım olur.";
			link.l1 = "Pekâlâ, Henrick. Kabul ediyorum. Açıkçası, bir daha asla bana vermeyeceğini düşünmüştüm.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Hiç şansın yok. Yarım milyon vaat et, hepsi senin olsun.";
			link.l1 = "Anlaştık! O zaman her zamanki gibi dalışa götürebilir miyim? Yarın başlayabilir miyim?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Aynen öyle.";
			link.l1 = "Teşekkürler! Görüşürüz, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben dalıp gitmişken, sen de hemen sandığımı karıştırmaya kalktın!","Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!";
			link.l1 = "Ahmak kız!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Dinle, silahını yerine koysan iyi olur. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Dinle, elinde kılıçla etrafta dolaşan bir ortaçağ şövalyesi gibi davranma. Onu yerine koy, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı rica ediyorum");
				link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde silahla dolaşmak tehlikeli. Ben de huzursuz olabilirim...","İnsanların silahlarını çekmiş halde önümden geçmelerinden hoşlanmıyorum. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıyorum.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

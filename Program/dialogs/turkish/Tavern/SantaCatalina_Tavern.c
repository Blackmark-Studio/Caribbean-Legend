// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Elbette, Helen. Ne oldu?","Ah, sonunda ne istediğini hatırladın mı?","Emin misin, iyi olduğuna? Başlamışsın beni endişelendirmeye. Belki bir hekime görünmelisin? ","Pekala, Helen. Biraz uyu, temiz hava al – kısacası, biraz ara ver. Sonra geri gel. Tamam mı?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Hayır, aslında hiçbir şey yok.","Hayır, hayır, sizi rahatsız ettiğim için özür dilerim.","Muhtemelen haklısın...","Evet, muhtemelen haklısın. En iyisi böyle yapmak.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Dinle, "+npchar.name+", Jan Svenson kimdir ve onu nasıl bulabilirim?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Dinle, bu kasabaya bir simyacı geldi mi, bir hekim? İtalyan, otuz yaşlarında, adı Gino Gvineili. Onunla ilgili bir şey duydun mu?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "Orman Şeytanı'nın kim olduğunu bilmeyen bir adamla ilk kez karşılaşıyorum. O lakabı ona İspanyollar taktı, ve tam on beş yıl önce Providence Adası'ndan o korsanın başı için bir çuval altın ödül koydular! Evet, yıllar su gibi akıp gidiyor... İnsanlar artık bizim Jan'ı unutmaya başladı bile. Belki de gerçekten dinlenme zamanı gelmiştir onun için.";
			link.l1 = "Buraya daha yeni geldim ve pek bir şey bilmiyorum...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Eğer geçmişle ilgileniyorsan, sana bir tarih kitabı satabilirim. Birçok kişi buna servet öderdi, ama ben...";
			link.l2 = "Bana lafı dolandırma! Sana bir soru sordum. Tekrar ediyorum: Jan Svenson nerede yaşıyor? Onunla konuşmam gereken ciddi bir mesele var.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Belediye başkanımızın konutunun karşısındaki köşkte, çeşmenin yanında oturuyor. Ama şu sıralar zor günler geçiriyor, o yüzden çok önemli bir işiniz yoksa onu rahatsız etmenizi tavsiye etmem.";
			link.l1 = "Nedenmiş?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Onun gözde kızı Helen, nam-ı diğer Rumba, merhum eski dostu Shawn McArthur’un kızı, ortadan kayboldu. Huzur içinde yatsın, yaşlı dost... Jan, kendi çocuğu olmadığı için o genç şeytanı öz kızı gibi görür. Ama kız, 'Rainbow' adlı şilebi ve tüm mürettebatıyla birlikte sırra kadem bastı\nKıza üzülüyorum. Ender bir güzellik, akıllı da. Ateş gibi canlı ve asi, bu yüzden ona Rumba derlerdi! Babası ona bildiği her şeyi öğretti, gemiyi ona bıraktı ve mürettebatın tamamı yanında kaldı. En yaşlı deniz kurtları bile onu kaptan olarak kabul etti...";
			link.l1 = "Bir kadın korsan mı? Ona ne olmuş olabilir?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Kim bilir... Bir hafta o kadar uzun bir süre değil, ama MacArthur'un dul eşi kızına bir şey olduğuna emin ve Svenson'u da buna ikna etti. Adamlarını topladı ve aramaya bizzat başladı, ama şimdiye kadar bir sonuç yok. 'Rainbow' ve mürettebatı adeta ortadan kayboldu\nGladys'i nerede bulacağını sana bin sekizliğe söyleyebilirim.";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "Bilginiz epey pahalıya patladı ama ilgimi çektiniz. Alın paranız. Onu nerede bulabilirim?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Yapma. Gerekirse kendim hallederim. Hoşça kal, hikaye için teşekkürler!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Evi iskeleye yakın, bağlama yerinin solunda. Ama muhtemelen orada değildir. Tüm gününü kalenin duvarlarının etrafında dolaşarak, sevgili kızını gözetleyerek geçirir. Gözyaşlarını çoktan tüketmiş olmalı.";
			link.l1 = "Hikaye için teşekkürler! Hoşça kal, dostum!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hayır, duymadım. Şifacılarımız ve hekimlerimiz var, ama o isimde biri yok.","Böylesine tuhaf bir ismi ilk kez duyuyorum. Hayır, bahsettiğiniz adam hiç buraya gelmedi.","Burada hiç simyacımız yok. Hekimlerimiz var, ama o kadar tuhaf bir isme sahip olanı yok.");
			link.l1 = "Anladım. Ne yazık. Aramaya devam edeceğim!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

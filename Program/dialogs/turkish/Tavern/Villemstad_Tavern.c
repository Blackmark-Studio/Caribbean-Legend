// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm söylentiler "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Tam da bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Aynı şeyleri papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unutmuşum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Adada ciddi bir sorun çıktığını duydum... Köleler mi?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Portekizli Bart denen alçak herifin sonunda adalete kavuştuğunu duydum! Hapiste mi? İnfazı ne zaman olacak biliyor musun? Gelip izlemek istiyorum, o pislikle bir hesabım var...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Dinle, "+npchar.name+", yeni bir güzel garson aldığını duydum... ve şimdiden kaybolmuş mu?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Söyle bakalım, "+npchar.name+", Betsy'nin kaybolduğu gece, etrafta şüpheli birini fark ettin mi? Belki biriyle konuşuyordu?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{			
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "Pekala, "+npchar.name+", iyi haber – değerli garsonun sağ ve sapasağlam. Romunu yeniden stoklaman gerekecek, yakında insanlar geri dönmeye başlayacak.";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "Pekala, "+npchar.name+", işte oldu – o çok değerli garsonun geri döndü. Rom stoklamaya başlasan iyi olur, yakında insanlar tekrar gelmeye başlayacak.";
						link.l1.go = "TBP_Tavern3_21_1";
					}
				
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Böylesi bir karmaşa daha önce hiç görülmedi... Binlerce zenci isyan etti. İki plantasyon tamamen yakıldı ve sahiplerinin her biri öldürüldü. Komutan, kölelerin şehre saldırmasından endişe ediyor, bu yüzden sıkıyönetim ilan etti. Ve bütün bunlar, biri Tamango adında bir erkek, diğeri Isauri adında bir kadın iki zenci yüzünden başladı...";
			link.l1 = "Oldukça dramatik geliyor. Anlat bakalım, kim bu zenciler?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango ve Izaura - Blenheim plantasyonunda köleydiler, ilk yakılan plantasyondu. Bu iki Siyah insan birbirini seviyordu. Ama bir plantasyon sahibinin oğlu Leonsio, Avrupa'dan geldi ve kıza göz koydu. Izaura'yı kendine cariye yapmak istedi. Siyah adam Tamango bu fikre hiç sıcak bakmadı, Izaura da öyle; o gerçekten bu kara şeytana aşıktı. Tamango, Afrika'da bir tür reis ya da öyle bir şeymiş... Kocaman bir adam - günah kadar kara ve baltayla ölümcül, diğer Siyahlar hem korkar hem saygı duyardı ona. Bu adam diğer köleleri isyana sürükledi. Gece bekçilere saldırdılar, büyük evin dışında kalan tüm beyazları öldürdüler, melezleri de. Sonra Izaura plantasyonun kapılarını açtı ve isyancılar içerideki herkesi katletti. Blenheim yerle bir edildi. Sonra köleler ormana kaçıp kayboldular...";
			link.l1 = "Eh, bu da hikaye mi şimdi, roman konusu gibi! Bildiğin köle isyanı, tıpkı Antik Roma’daki gibi. Bu kadarını nasıl öğrendin peki, anlat bakalım?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Söylentiler, efendim, dünya onlarla dolup taşıyor. Rom dilleri çözer, tek yapmanız gereken dinlemek...";
			link.l1 = "Peki, sonunda ne oldu? O zencileri bulabildiler mi?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ha, hiç şansı yok! Takviye kuvvetler nihayet gelene kadar kimse ormana adımını atmadı. Sonra bir Şirket savaş gemisi askerlerle birlikte geldi ve adayı aradılar. Tek bir kaçak zencinin izi bile bulunamadı.";
			link.l1 = "Vay canına! Bin siyah bir anda ortadan kayboldu, ha?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Aslında suya.";
			link.l1 = "Ne diyorsun, "+npchar.name+"? Sen de benim kadar iyi biliyorsun ki zenciler yüzemez.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... ah, yok, o zenciler öyle kolayca köpekbalığı yemi olmaz. Mesele şu ki, isyandan sonraki gece, iskeleden bir barque kayboldu. Eğer o Tamango ve zencileri işin içinde değilse, beni zenciye boya, banjo çalayım, senin için dans edeyim! O yüzden artık adada değiller.";
			link.l1 = "Ha, şimdi de bunu duydum ya, "+npchar.name+". Bir grup yarı vahşi zencinin yelken açıp gemi sürebileceğine inanmamı mı bekliyorsun? Gine'den bir grup maymunun gemiyle buraya gelmesini daha olası bulurum.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Ben de inanamadım, efendim, ama kayıp gemi ortada. Belki o zencilerden biri eskiden bir gemide kamarotluk yapmıştır da denizcilikten bir şeyler kapmıştır. Belki de kara büyü yaptılar, kim bilir! Yine uğrayın, görüşelim, "+pchar.name+", bir dahaki sefere sana daha çok hikaye anlatırım.";
			link.l1 = "Teşekkürler! Eh, artık gitme vakti benim için.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Evet, doğru. O korsanı yakaladılar. Ve nasıl yakaladıklarına inanabiliyor musun? Onu denizin ortasında, küçücük bir sandalda tek başına bulmuşlar. Farelerle dolu ambarın içine atılmadan önce tek kelime etmemiş. Düşünsene, bu kadar tehlikeli bir korsanın böyle acemi bir şekilde yakalanması gerçekten komik!";
			link.l1 = "Peki, neden denizde tamamen yalnızdı?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Muhtemelen yandaşlarıyla yollarını ayırmaya karar verdi, hiç şüphe yok... Ganimeti adilce paylaşamamışlar. Şimdi Şirket’in elinde ve o adamlar şakadan hiç hoşlanmaz. Söylenene göre, Şirket’in teknelerinden birini içinde değerli bir şeyle ele geçirmiş. Görünüşe bakılırsa, ondan bazı bilgileri almak istedikleri için hâlâ ipte sallanmıyor.";
			link.l1 = "Peki, idamının ne zaman olacağını biliyor musun?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nobody knows. I think once the Company finds out what it wants, they'll fasten a hemp tie around his neck. The Portuguese is in prison right now under reliable guard\nRecently they brought his boatswain over here as well. His story was even more surprising; he turned himself in to the Dutch in Philipsburg. So, they've set him up in a cell right next to his former captain, so they're neighbours now, he-he...";
			link.l1 = "Mucizeler gerçekten oluyor! Tamam, haberleri takip edeceğim. O idamı kaçırmak istemem. Hoşça kal, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Ah, keşke onu görebilseydiniz, Kaptan! Betsy... ne zarafet, ne güzel bir gülüş! Erkekler sırf onu görmek için buraya akın ederdi. Ve bıraktıkları gümüşler... Ama üç gün önce işe gelmedi. Tabii ki adamlarımı evine gönderdim, ama orada yoktu. Her yer dağınıktı, eşyaları gitmişti\nArtık ne düşüneceğimi bilemiyorum. Muhafızlar her zamanki gibi umursamadı. Kaybolan bir kızı aramaktan daha önemli işleri olduğunu söylediler. Muhtemelen dışarı çıkmıştır, yakında döner dediler. Kaptan, belki siz bulabilirsiniz onu? Onu buraya geri getirirseniz, size yüz dublon ödeyeceğim. Onu kaybedemem, anlıyor musunuz? O gerçek bir hazine! Ne pahasına olursa olsun geri getirmeliyim!";
			link.l1 = "Bakalım ne yapabilirim. Kaybolmadan önce garip davrandı mı, ya da kötü bir haber aldı mı?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Muhtemelen sadece kaçıp gitmiş bir kızı mı arayayım? Yapacak daha önemli işlerim var. Sen hallet.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "Kaybolmadan önceki son gününde, keyfi yerindeydi, hatta mutluydu! Hiçbir sorun belirtisi yoktu, gitmekten hiç bahsetmedi. Bir anda ortadan kayboldu!";
			link.l1 = "İlginç... Onun evini nerede bulabilirim?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "O, caddenin biraz ilerisinde, mavi balkonlu konağın tam karşısındaki evin arkasındaki kulübede yaşıyordu. Buradan çok uzak değil.";
			link.l1 = "Pekala, o zaman vakit kaybetmeyeceğim. Bir şey bulursam, sana haber veririm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Şüpheli mi? Etrafında her zaman bir sürü talip olurdu, hepsi de kendine göre şüpheliydi! Oldukça cilveli biriydi, dikkat çekmeyi iyi bilirdi.";
			link.l1 = "Bunu zaten anlamıştım"+GetSexPhrase(""," dışarı")+" zaten. Ama öne çıkan biri oldu mu?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... Aslında, bir tane vardı. O akşam ona değerli taşlarla süslü bir kolye verdi. Burada oturdu, gözleri ondan hiç ayrılmadı, bütün gece etrafında dolaştı.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "Şu kolye, tesadüfen, tam olarak bu olmasın? (Dilenciden aldığın kabartmayı göster)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Mücevherli bir kolye diyorsun...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "İşte bu! Aynen öyle! Kaptan, yoksa bir şey mi buldunuz?";
			link.l1 = "Detayları sonra anlatırım, "+npchar.name+", şu anda kaybedecek zaman yok.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Given: Cameo pendant", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "Harika, Kaptan! Onu bir daha asla göremeyeceğimi düşünmeye başlamıştım. Peki ne oldu? Gerçekten kaçmak mı istemiş?";
			link.l1 = "Diyelim ki geçmişinden kalan bazı sorunlarla uğraşmak zorunda kaldı. Ama görünen o ki, artık hepsi geride kaldı ve yakında tekrar işinin başında olacak.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Şey, diyelim ki senin sıkıcı suratına bakmaktan biraz mola vermesi gerekiyordu. Ha-ha! Surat asma, şaka yapıyorum. Her hanımın küçük sırları olmalı...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Asıl önemli olan, onun işe geri dönecek olması. Ödülünü hak ettin, Kaptan. Al bakalım – anlaştığımız gibi yüz doblon. Ayrıca, şu haritayı da al. Müşterilerden biri burada bırakıp bir daha dönmedi. Görünüşe göre bir hazineye götürüyor.";
			link.l1 = "Peki o zaman, bir bakarım. Teşekkürler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Asıl önemli olan, onun tekrar işe dönecek olması. Ödülünü hak ettin, Kaptan. Al bakalım – anlaştığımız gibi yüz doblon. Ayrıca, şu haritayı da al. Müşterilerden biri burada bırakıp bir daha gelmedi. Görünüşe göre bir hazineye götürüyor.";
			link.l1 = "Pekala, bir bakarım. Teşekkürler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "Hayatımı kurtardınız, kaptan! Onu bir daha göreceğimden neredeyse umudumu kesmiştim... Peki, aslında ne oldu? Gerçekten kaçmayı mı planlıyormuş? Bunu ona kendim sormaya cesaret edemedim.";
			link.l1 = "Diyelim ki geçmişten kalan bazı işleriyle ilgilenmek zorunda kaldı. Ama görünen o ki, artık her şey geride kaldı ve yakında tekrar işinin başında olacak.";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "Şey, diyelim ki senin sıkıcı suratına bakmaktan biraz mola vermesi gerekiyordu. Ha-ha! Öyle surat asma, sadece şaka yapıyorum. Her kadının küçük sırları olmalı...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "Asıl önemli olan, onun işe geri dönmesi. Ödülünü hak ettin kaptan. Al bakalım – anlaştığımız gibi yüz dublon. Ayrıca, şu haritayı da al. Misafirlerden biri burada bırakıp bir daha hiç dönmedi. Görünüşe bakılırsa, bu harita bir hazineye götürüyor.";
			link.l1 = "Pekala, bir bakarım. Teşekkürler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "Önemli olan, onun işe geri dönmüş olması. Ödülünü hak ettin, kaptan. Al bakalım – anlaştığımız gibi yüz dublon. Ayrıca, şu haritayı da al. Misafirlerden biri burada bırakıp bir daha geri gelmedi. Görünüşe bakılırsa, bu harita bir hazineye götürüyor.";
			link.l1 = "Pekâlâ, bir bakarım. Teşekkürler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

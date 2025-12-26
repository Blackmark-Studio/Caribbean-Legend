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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...ve Kutsal Ruh adına. Âmin.";
			link.l1 = "Kiliselerde nadiren asker görürüm.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Birçokları inançla kılıcın bağdaşmadığını düşünür. Ama bir cerrah iyileştirmek için kesmez mi? Bir baba korumak için cezalandırmaz mı?";
			link.l1 = "Kulağa bahane gibi geliyor.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Bunda bir bilgelik var. Bazen acımasızlık gerekli olur.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Yanılıyorsun. Bu bir gerekçe değil – bu bir anlayış. Hizmetime ilk başladığımda, her ölüm… zordu. Ama sonra… gözlerim açıldı. 'Zulüm, yüce sevginin tezahürüdür.'";
			link.l1 = "Seni dualarınla baş başa bırakıyorum.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Evet... evet! Beni bu yola yönlendiren adam tam olarak böyle söyledi. 'Güçsüz merhamet işe yaramaz, elde olmayan bir kılıç gibidir.'";
			link.l1 = "Seni dualarınla baş başa bırakıyorum.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Hepimiz için dua et. Yaptıklarımız ve daha yapmamız gerekenler için.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Yüzde yedi eksik. Geçen sefer beşti. Terk edilmiş bir bahçede otlar gibi çoğalıyorlar...";
			link.l1 = "Kasabada yeni bir vali mi var?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Ne? Ah, hayır. Ekselansları orada, köşede. Ben Kraliyet Müfettişi Don Fernando de Alamida.";
			link.l1 = "Zor bir iş olmalı.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Yolsuzlukla savaşmanın en zor yanı ne biliyor musun? Suçlular illa kötü insanlar olmayabiliyor. Onların da çocukları, aileleri var. Ve her seferinde kendine hatırlatmalısın: Zehir, altın bir kupada sunulsa da zehirdir.";
			link.l1 = "Ama insan bu kadar acımasızca yargılayabilir mi? Hepimiz insanız...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Sen çok yumuşaksın. Onları ancak hapis adam eder.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Kurtlara merhamet, koyunlara zulümdür. Böyle demişti... bilge bir adam. Ve her geçen gün, onun sözlerindeki hikmeti daha iyi anlıyorum.";
			link.l1 = "Artık seni işinden alıkoymayacağım.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. Bilir misin, ben de eskiden böyle düşünürdüm. Ama hapishane fazla basit. Daha fazlası gerek... Arınma.";
			link.l1 = "Artık seni işinden alıkoymayacağım.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Evet. Evraklar beklemez. Ama bazen burada her bir rakamın ardında birinin kaderi saklanıyor gibi geliyor bana.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Dikkatle dinliyorum, "+GetAddress_Form(NPChar)+"? Böyle sokakta, doğrudan yanıma gelmene sebep olan neydi?";
			link.l1 = "Sen diğerlerinden ayrılıyorsun.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, kraliyet müfettişi. Bugün ilk defa böyle meraklı biriyle karşılaşıyorum. Herkes saklanıyor, herkes benden korkuyor. Oysa dürüst birinin korkacak hiçbir şeyi yoktur. Bu bize ne anlatıyor?";
			link.l1 = "İtibarının onları korkuttuğunu mu düşünüyorsun?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Dürüst insanların az olduğunu mu söylüyorsun?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Eğlenceli. Ben de öyle düşünmüştüm. Ta ki anladım ki - korku arındırır. İnsan korkunca, daha dürüst olur. Gerçek doğasına yaklaşır. Tanrı'ya da.";
			link.l1 = "İlginç bir düşünce. Gitmeliyim. İyi günler, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "İlginç... Tıpkı tanıdığım biri gibi düşünüyorsun. Ne yazık ki herkes bu gerçeği kabul edemiyor.";
			link.l1 = "İlginç bir düşünce. Gitmeliyim. İyi günler, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "İyi mi? Evet, belki. Yeter ki doğru olsun.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_DlgExit");
		break;
		
		case "Alamida_repeat":
			dialog.text = "Başka bir şey var mı, Kaptan?";
			link.l1 = "Hayır, don Fernando, sadece merhaba demek istedim, başka bir şey değil.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Kılıçlı bir hanımefendi mi? Doğrusu, böyle bir manzarayı göreceğim aklıma gelmezdi. Peki, sen kimsin, señorita, 'Kutsal Merhamet'e saldırmaya cüret eden?";
				link.l1 = "Kaptan Hellen McArthur. Ve yüzündeki o şaşkın ifadeyi çok iyi tanıyorum.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Nasıl cüret edersin?! 'Kutsal Merhamet'e saldırmak mı?! Kralın iradesini taşıyan bir gemiye ve... Neyse. Madem buradasın, söyle bana - neden? Neden bu deliliği seçtin?";
				link.l1 = "Ben bir korsanım. Ve senin gemin kesinlikle hazinelerle dolu.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Böyle güzel bir gemi... Ona sahip olmalıyım.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Ben senin ülkenin düşmanıyım, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Sadece öylesine. Neden olmasın?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Meryem Ana'ya, gemimizin koruyucusuna ne kadar da benziyorsun... O da senin kadar güzel. Ama O, doğru olanları korur, sen ise...";
			link.l1 = "Gemini almak için geldim. Ve iltifatlar burada işe yaramaz, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Ne yazık. O zaman sana alçakgönüllülüğü ben öğreteceğim. Zorla, çünkü başka yolu yok.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah evet. Tabii ki. Altın. Hep altın. Ruhları çürüten zehir. Onun için öleceksin.";
			link.l1 = "Abartma. Bu sadece iş.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Ambarımdaki her bir sikke, günahkârların arınma bedeli. İstiyor musun? O zaman onların kaderini paylaş.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Pek çok kişi 'Kutsal Merhamet'i arzuladı. Onun güzelliği nice kaptanın sonu oldu.";
			link.l1 = "O halde onu ilk talep eden ben olacağım.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Güçsüz merhamet işe yaramaz, elde olmayan bir kılıç gibi. Bugün bu dersi alacaksın.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Demek bu kadar. Bir diğeri de İmparatorluğun görkemini kıskanıyor.";
			link.l1 = "Hangi büyüklük? Senin katı kuralların bu dünyayı geride tutuyor.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Kendine yalan söyleme. İspanya korkusu seni daha dürüst yapıyor. Gerçek doğana daha yakın. Şimdi kendin göreceksin.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Deli.   Yoksa bana bir sınav olarak mı gönderildin?";
			link.l1 = "Her şeyin bir nedeni olması gerekmez, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Böyle insanlar en tehlikelisi, dedi. Ama bu sadece savaşta elimi daha da güçlendirecek.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_1");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Böylesine bir ruh gücü... Böylesine bir irade...";
				link.l1 = "Şaşırdın mı?";
			}
			else
			{
				dialog.text = "Fena değil. Uzun zamandır böylesine dişe dokunur bir rakiple karşılaşmamıştım.";
				link.l1 = "Sana dinlenmeye vakit vermeyeceğim.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Böyle bir sınavdan... böyle bir güzellikten uyarılmıştım; bir savaşçının inancını sarsacak kadar güçlü bir güzellikten.";
				link.l1 = "Basit şeyleri her zaman bu kadar karmaşıklaştırır mısınız, don Fernando?";
			}
			else
			{
				dialog.text = "Rab, haklı bir davaya hizmet edenlere güç verir. Ama... bazen artık neye hizmet ettiğimden emin olamıyorum.";
				link.l1 = "Şüphelerin mi var?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Basit mi? Hayır... Bunun daha derin bir anlamı olmalı. Bu bir sınav. Yanılıyor olamam.";
			}
			else
			{
				dialog.text = "Hayır. Bana asla şüphe etmemeyi öğretti. Asla.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_2");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Bekle... Bekle. Kazandın. Yaralıyım, kan kaybediyorum. Ölmeden önce dua etmeme izin ver.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Tanrım... Günahlarımı affet ve bu sınav saatinde bana güç ver. Düşmüş yoldaşlarımın ruhlarını kutsal kıl. Sadık denizcilerdi, adaleti taşıdıklarına inanarak öldüler\nBaba, senin öğretilerinle yaşamaya, adaletsizliğe karşı savaşmaya çalıştım. Ama oğlun Alamida ailesinin onurunu lekeledi. Beni affet\nVatanım... Sana sadakatle ve dürüstçe hizmet etmeye yemin etmiştim. Ama öfkem, hırsım... Savaşmaya çalıştığım şeye dönüştüm\nDiego... Belki de yalan söyledi? Bunca zaman... Eğer öyleyse, vay halime\nVe bu kadını da kutsal kıl, Tanrım. Belki de son merhametinle onu bana gönderdin... ne kadar saptığımı göreyim diye. Amin.";
			}
			else
			{
				dialog.text = "Tanrım... Günahlarımı affet ve bu sınav saatinde bana güç ver. Düşmüş yoldaşlarımın ruhlarını kutsa. Sadık denizcilerdi, adaleti taşıdıklarına inanarak öldüler\nBaba, senin öğretilerinle yaşamaya, adaletsizliğe karşı savaşmaya çalıştım. Ama oğlun Alamida ailesinin onurunu lekeledi. Beni affet\nVatanım... Sana sadakatle ve dürüstlükle hizmet etmeye yemin etmiştim. Ama öfkem, hırsım... Savaşmaya çalıştığım şeye dönüştüm\nDiego... Belki de yalan söyledi? Bunca zaman... Eğer öyleyse, yazıklar olsun bana\nKutsal Meryem Ana, Tanrı'ya bizim için dua et ve bize merhametini bağışla. Âmin.";
			}
			link.l1 = "Sizi tanıyamadım, don Fernando. Şimdi bambaşka biri gibisiniz. Ve kimin hakkında konuşuyordunuz?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_3");
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Kaptanım, tebrikler! Ne çetin bir savaştı. O kaptan gerçekten ustaydı, hem de çok ustaydı. Ama siz... siz ondan da iyiydiniz. Sizinle ne kadar gurur duyduğumu anlatamam...";
			link.l1 = "Teşekkür ederim, sevgilim. Yaralandın mı?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Hayır, hayır. Ama birkaç kez ucundayız sandım – hem gemiye çıkmadan önce hem de sırasında. Peki ya sen, iyi misin?";
			link.l1 = "İyiyim, tekrar teşekkür ederim. Kabinde dinlen, yakında sana katılacağım.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, iyi misin? Elimden geldiğince çabuk geldim, tamam mı.";
			link.l1 = "İyiyim, teşekkür ederim canım. Ama gerçekten zorlu bir mücadeleydi.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Sevindim! Ama... Dinle, Charles? Neden bu insanlara saldırdık? Tanrı bizi bunun için affetmeyecek, hayır. Bu gemi... büyük bir tapınak gibi. Onu gördüğümde, kalbim titredi, tıpkı ilk kez gerçek bir kilise gördüğümdeki gibi, sadece kitaplarda değil. Ve şimdi kanıyor!";
			link.l1 = "Mary... Biliyorsun, görünüşler aldatıcı olabilir. Ve dindarlık maskesinin ardında, senin gibi saf inananlardan para alanlar vardı. Anlıyor musun?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Ben... Ben sana inanıyorum, Charles. Peki. Ama... burada bulduğumuz altının en azından bir kısmını gerçekten ihtiyacı olanlara bağışlasak? Bu, içimi rahatlatırdı.";
			link.l1 = "Bunu yapacağız, Mary. Söz veriyorum. Şimdi düşüncelerini toparla ve sakinleşmeye çalış. Her şey bitti.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha, güzel, zaferiniz için tebrikler kaptan! İşte ben buna ticaret derim! Bu kalyonda ne ganimet varmış!..";
			link.l1 = "Bugün gülümsemen her zamankinden de geniş, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Tabii ki! Ne ganimet ama. Ve ne dövüştü. Devrimi hatırlattı bana. Ve ayrıca... heh.";
			link.l1 = "Ne oldu Tommy? Hadi, söyle bakalım.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Bütün gemiyi yüzen bir katedrale çevirmişler. Her yerden altın toplamışlar. Gerçekten tam Katolik yobazları! Utanç verici ve gülünç.";
			link.l1 = "Bu bir hazine gemisi, Tommy. Kilise gemisi değil.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Bizim için pek bir farkı yok. Yine de o dons ve papistlere iyi bir ders vermek hoşuma gitti! İkisine de tahammülüm yok. Bugün gerçekten çok keyif aldım, ha-ha-ha!";
			link.l1 = "Sen hiç değişmiyorsun! Peki, dağılın. Burada her şey kontrol altında.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Kaptan Charles, zaferi kazandık. Bu zorlu bir savaştı. Tichingitu bile zorlandı, ki ben köydeki en iyi savaşçılardan biriyim.";
				link.l1 = "Doğru, dostum. Gerçekten de değerli rakiplerdi.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, gemi artık bizim.";
				link.l1 = "Çok iyi, Tichingitu. Ben de burada işimi yeni bitirdim.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Kaptan Paterson, gemideki son direniş de bastırıldı.";
				link.l1 = "Geç kaldın, Tich! Bir dahaki sefere yanımda kal. Yalnız başıma halledemezdim demiyorum, yanlış anlama...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Kaptan McArthur, iyi misiniz?";
				link.l1 = "Evet, Tichingitu, iyiyim, sorduğun için teşekkür ederim. Ve kaptanından şüphe etmeyi bırak artık – bunun üstesinden gayet güzel geldim.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Ruhlar bana bunu dövüş sırasında söylüyor. Ve neden onları öldürdüğümü soruyorlar. Şimdi ben de sana aynı şeyi soruyorum. Tichingitu onların gözlerinde gördü, onlar kötü insanlar değillerdi. Henüz değil.";
				link.l1 = "Ah, sana ne diyebilirim ki? Bir cevabım yok, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Sana bir soru sormak istiyorum, Kaptan de Montoya.";
				link.l1 = "Dinliyorum.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu sana bir soru sormak istiyor, Kaptan William, izin verirsen.";
				link.l1 = "Kabul edildi.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Sana güveniyorum, ama senin için endişeleniyorum, kaptan.";
				link.l1 = "Pekala, pekala. Gözlerinde bana başka bir şey sormak istediğini görebiliyorum.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, dediğiniz gibi, kaptan. Burada işimiz bitti mi?";
				link.l1 = "Evet. Biraz daha etrafa bakacağım, sonra diğerlerine katılırım.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Bu insanlar, seninle aynı kabileden değil mi? İspanyol da değiller mi? Neden saldırmaya karar verdin?";
				link.l1 = "Doğru. Ama Kızılderili kabileleri de birbirleriyle savaşmıyor mu? Ya da bir kabile içinde de kavgalar ve husumetler olmuyor mu?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Bu gemi kiliseye benziyor. Kiliseyi ve beyaz tanrıyı sevmiyor musun?";
				link.l1 = "Hiç de değil. Ama bu sadece süs, anlıyor musun? Burası bir hazine gemisi. Gerçi senin halkının vergiden bile haberi yokmuş, öyle duydum. Şanslı keratalar.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Evet. Doğruyu söyle. Kaptan MacArthur, neden bu yüzen kiliseye saldırıyoruz?";
				link.l1 = "Yüzen bir kilise, ha-ha-ha! Hayır, hayır. Bu bir hazine gemisi. Hmm, tam olarak anlamadığını görüyorum. Şey, altın taşıyorlardı. Fernando de Alamida'yı yendiğimi Jan'a söylediğimde nasıl gururlanacağını hayal edebiliyorum!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, doğru söylüyorsun kaptan. Ama bu, Kızılderililerde beyaz adamlara göre daha az olur.";
				link.l1 = "Belki. Şey, bu adam... bana engel oluyordu.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Doğruyu söylemek gerekirse, Maskogi'nin ne şatosu var ne de vergisi.";
				link.l1 = "Aynen öyle. Gidebilirsin, zaten geç kaldın. Sonra bu güzel kalyonla ne yapacağımıza karar veririz. Bu hantal gemileri sevmem ama, lanet olsun, bu gerçekten güzelmiş.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu da seninle gurur duyuyor, kaptan. Ve bu zorlu mücadeledeki zaferini kutluyor.";
				link.l1 = "Teşekkürler. Şimdi ganimeti paylaşmaya geçelim.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Müdahale mi ediyorsunuz, Señor de Montoya?";
			link.l1 = "Aynen öyle. Bu Takımadalar ikimize birden fazla. Üstelik burada devletimize çok daha fazla faydam dokunuyor. Kakao Yaprağı'nı hatırla – kardeşlerine iyilikten çok zarar verdi. Burada da durum aynı.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Şimdi anladım. Tichingitu gidebilir mi, kaptan?";
			link.l1 = "Evet, git. Ben de yakında size katılacağım.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Hey, bu silah sallama işi de ne böyle?! Hemen indir onu!","Silahını derhal indirmeni emrediyorum!","Hey, "+GetAddress_Form(NPChar)+", insanları korkutmaktan vazgeç! Silahını indir.");
			link.l1 = LinkRandPhrase("Pekala, onu kaldırıyorum...","Zaten yapıldı.","Dediğin gibi...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Siktir git!","Sanırım bunu kullanacağım!","Zamanı gelince onu kaldırırım.");
			link.l2.go = "fight";
		break;
		
	}
} 
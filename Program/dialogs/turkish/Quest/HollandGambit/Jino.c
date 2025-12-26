// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "Ah! Günaydın efendim. Buraya nasıl geldiniz?";
				link.l1 = "İyi günler, Gino. Birbirimizi tanıyalım. Ben Kaptan "+GetFullName(pchar)+" ve burada John'un izniyle bulunuyorum. Şunu açıkça söyleyeyim - sizin yardımınıza ihtiyacım var, ama ben de size yardımcı olabilirim.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah! Günaydın, efendim. Buraya nasıl geldiniz? Peki ya John nerede?";
				link.l1 = "Demek... Bu kapalı kapının ardında hep saklanan sendin! İlginç... John'a gelince... O artık yok. Ve bu ev artık bana ait. Ama endişelenme. Hadi birbirimizi tanıyalım. Sen kimsin, burada ne yapıyorsun?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Merhaba, "+pchar.name+". Yüzünden önemli bir şey bulduğunu anlıyorum. Gerçeğin Muhafızı'nın tüm parçalarını topladın mı?";
					link.l1 = "Kesinlikle! Üç eşyam da yanımda: hançer, harita ve pusula!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Merhaba, "+pchar.name+". Ne oldu? Yüzünde garip bir ifade var...";
					link.l1 = "Seninle konuşmam gereken bir şey var, Gino. Bu önemli.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+" Evet, hatırlıyorum, iki gün geçti ve Gerçeğin Muhafızı hakkında bir şeyler öğrenmek istiyorsun, değil mi?";
					link.l1 = "Evet, öylesin! Bir şeyler öğrenebildin mi?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "5.000 peso getirdin mi, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Tabii. Al parayı, neye ihtiyacın varsa al.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Ne yazık ki, şu anda yanımda para yok.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Ne yazık ki, "+pchar.name+", çok üzgünüm - hasta hayatını kaybetti. Durumu aniden kötüleşti ve çok hızlı bir şekilde vefat etti.";
					link.l1 = "Ne yazık... Tanrı ruhuna merhamet etsin!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Merhaba, "+pchar.name+" . Bir şey mi oldu? Çok endişeli görünüyorsun...";
					link.l1 = "Gino, senden alışılmadık bir ricam var! Gemimde yüksek ateşi olan bir adam var. Sayıklıyor ve kendinde değil... ona yardım edebilir misin?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", Hastayı bekliyorum. Acele et, onu buraya ne kadar çabuk getirirsen, kurtarma şansım o kadar yüksek olur.";
					link.l1 = "Evet, evet, hemen buraya getirilecek.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Onu tam zamanında getirdin, "+pchar.name+". Durumu kritik, ama hâlâ bir umut var.\nKaptan, malzemelerim tükenmek üzere ve ormanda toplamaya vaktimiz yok. Hepsini yerel aktarlardan 5.000 peso karşılığında almam gerek. Bu parayı sağlayabilir misiniz?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Tabii. Al parayı, ihtiyacın olan her şeyi satın al.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Ne yazık ki,  şu anda param yok.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Şu anda söyleyecek bir şeyim yok, "+pchar.name+". Hastanın hayatı için mücadele ediyorum. Hâlâ biraz umut var. Daha sonra yanıma gel, yakında sana daha kesin bir şey söyleyebileceğimi düşünüyorum.";
					link.l1 = "Pekala, Gino, sonra geri geleceğim.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Haberlerim var,"+pchar.name+". Adamınızın iyi olduğunu söyleyemem, ama hayatta. Hastalığı geriliyor ve bir ilerleme var. Açıkçası, iksirlerimin ona bu kadar fayda edeceğini beklemiyordum.";
					link.l1 = "Harika bir haber bu, Gino, ama söyle bakalım, onu ne zaman alabileceğim? Önümüzde uzun bir yol var ve zaman daralıyor.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Günaydın, Kaptan. Sizi görmek güzel.";
					link.l1 = "Hastamız nasıl, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Günaydın, Kaptan. Nasılsınız? Yardımıma ihtiyacınız var mı?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Evet. Gino, senin bilgili bir adam olduğunu düşünüyorum, belki Latince bile biliyorsundur...";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Sana farklı bir şeyim var. Küçük bir hediye. Al, şu kitaba bir bak.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Evet, Gino. Sana bu tabancayı göstermek istiyorum. Daha önce böyle bir şey gördün mü?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Sana tabancam için barut örneği getirdim.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "Tabanca için suçlamalar ne olacak? Henüz bir ipucu bulabildin mi?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, bir kaptanın günlüğünde bana yabancı gelen 'gord' kelimesine rastladım. Ne anlama geldiğini biliyor musun?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "İyi günler, Gino. Ben iyiyim, yardıma ihtiyacım yok. Sadece seni görmek ve biraz sohbet etmek istedim.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Benim adım Gino. Gino Gvineili. Ben bir bilim insanıyım. İşim, Bay Murdock için tozlar, karışımlar ve başka ilaçlar hazırlamak. Ama o gideli beri...";
			link.l1 = "Pekâlâ, ben "+GetFullName(pchar)+" . Kendi gemimin kaptanıyım. Demek simyacısın, öyle mi?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Not only am I an alchemist, but also a physician. I possess considerable knowledge of medicine. I know much about healing herbs, and I am able to brew mixtures and potions from them. But chemistry is my true calling; I do a great deal of experimenting, and some of my inventions might be of use to people like you.\nI know Latin, French, English, and Italian. My help will be indispensable if you are planning to run a drugstore as Mister Murdock did...";
			link.l1 = "Oho! Her gün böyle bilgili bir adamla karşılaşmıyor insan. Eczacılık işi güzel elbette, ama ben bir denizciyim... hm, bu kulağa benim için bile tuhaf geliyor... Neyse, eminim dost olacağız, Gino. Burada yaşamaya ve bilimsel işlerine devam edebilirsin...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "Ve eğer bir gün bir simyacıya, bir şifacıya ya da bir bilim insanına ihtiyacım olursa, kimi bulacağımı biliyorum... Söylesene, neden hep içeridesin? Hiç dışarı çıkmaz mısın?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Deneylerim için malzeme ya da bitki almam gerektiğinde dışarı çıkarım. Yalnız yaşamayı seviyorum, bu benim tarzım. Hayatımı bilime adadım ve sıradan yaşama hiç ilgi duymuyorum. Kitaplar, yazılar, deney tüpleri, imbikler...\nBay Murdock, ona ilaç yapmam karşılığında bana böyle bir fırsat sundu.";
			link.l1 = "Artık daha fazla vaktin olacak, Gino. Ama yardıma ihtiyacım olursa, bazı deneylerine ayırdığın zamandan feragat etmen gerekecek, anlaştık mı?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Elbette, Kaptan. Size Kaptan diyeceğim, "+GetAddress_Form(NPChar)+", sakıncası yoksa? Tüm araştırmalarımı burada bırakacağım, olur da pratik becerilerime ya da teorik bilgime ihtiyaç duyarsanız.";
			link.l1 = "Harika. Birbirimizi bu kadar çabuk anladığımıza sevindim. Masrafların için de endişelenme, arada sırada sana makul miktarlarda para bırakacağım, ya ben ya da veznedarım.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Teşekkür ederim, Kaptan. Fazla bir şeye ihtiyacım yok... Kaptan, bir fikrim var... neden biraz simya öğrenmiyorsunuz? Belki size gerçekten faydası dokunur.";
			link.l1 = "Hm. Bir keresinde ağabeyim bana şöyle demişti: Kendi işini kendi ellerinle yapmaktan çekinme. Yani, neden olmasın. Ne gösterebilirsin bana?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Elbette, demiri altına çeviremeyeceksin, bu imkansız... en azından şimdilik. Ama talimatlara göre malzemeleri karıştırarak iksirler ya da başka faydalı şeyler yapmayı öğrenebilirsin. Al, bu torbayı al. İçinde yeni başlayan bir simyacının ihtiyacı olan her şey var: deney tüpleri, şişeler, imbikler, damıtıcılar, spatulalar, cam borular, bir ocak ve daha fazlası...";
			link.l1 = "Büyüleyici!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("You have received an alchemist's kit");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bir iksir ya da eşya yapmak için önce tarifini bilmelisin. Tarifleri tüccarlardan satın alabilir ya da farklı yerlerde bulabilirsin. Bir tarifi inceledikten sonra, gereken tüm malzemeleri toplamalı ve orada yazanı harfiyen uygulamalısın.\n Simya aletlerini kullan, havan ve tokmak bul ya da satın al, bir de pota ara—ne yazık ki fazladan bir tane veremem. Otlar, içkiler, iksirler, mineraller, hatta çer çöp—doğru tarif ve aletlerin varsa hepsi işine yarar.";
			link.l1 = "Anladım. Boş zamanımda bir şeyler karıştırmayı denerim. Teşekkürler, Gino! Bana basit bir tarif verebilir misin? Başlamak için bir şey olsun yeter.";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Kolay bir işim yok... ama al, bu panzehir tarifini sana vereyim. Sanırım bu görevin üstesinden gelebilirsin. Al bakalım.";
			link.l1 = "Teşekkür ederim! Bunu öğreneceğim. Şimdi hoşça kal, Gino! Evime göz kulak ol, buraya pek sık uğrayamayacağım gibi görünüyor, bu yüzden sadece kendi odanı değil, binanın geri kalanını da kullanabilirsin.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("You have received an antidote recipe");
			PlaySound("interface\notebook.wav");
			Log_Info("You need to have the Alchemy skill in order to craft potions, amulets and items!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Evet, Kaptan, antik Romalıların dilini biliyorum. Her bilginin, özellikle de bir şifacı ya da simyacının Latince bilmesi gerekir. Latince bilgime ihtiyacınız var mı?";
			link.l1 = "Evet. Gino, beni aptal sanma ama... yani, bunu nasıl anlatsam...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Açık konuş, Kaptan. Çekinme.";
			link.l1 = "Pekala. Benim için birkaç bilimsel Latince deyiş hazırlar mısın? Bak, şöyle bir durum var... Kendini 'bilgili' sanan bir adam var ve bazen bana karşı üstünlüğünü göstermek için Latince ifadeler kullanıyor. Mesela... 'si vis pacem, para bellum' gibi...";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', yani?";
			link.l1 = "Evet, evet. Onları öğrenmek istiyorum ki o kibirli abimi... yani arkadaşımı alt edebileyim.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "İsteğinizde garip ya da utanç verici bir şey yok, Kaptan. Tarihe geçmiş eskilerin özdeyişlerini bilmek sizi eğitimli bir insan yapar. Alın, işte istediğiniz metin.";
			link.l1 = "Teşekkürler, Gino! Bunu gerçekten takdir ediyorum! Boş vaktimde okuyacağım...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("You have given Lavoisier's chemistry textbook");
			dialog.text = "Göster bana... (okuyor) İmkansız! 'Küçük bir hediye' mi diyorsun? Bu kitap paha biçilemez! Bunu nereden buldun?! Bu... gerçek bir hazine!";
			link.l1 = "Beğenmene sevindim.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Okuyorum) İnanılmaz! Bunun adını bile duymamıştım... peki ya bu? Buradaki hiçbir şeyi anlamıyorum... ama anlayacağım, kahretsin! Çok yakında laboratuvarımda işler kaynayacak! "+pchar.name+",   bana   ne   verdiğinin   farkında   bile   değilsin...";
			link.l1 = "Neden olmasın? Elbette isterim. Bir bilim insanı için bilimsel bir kitap...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "Ama bu mucizenin yazarı kim? Antoine-Laurent de Lavoisier, Fransa... Hiç duymadım. Ama dur! Bu nasıl mümkün olabilir! Basım yılı 1789 mu? Ama nasıl...";
			link.l1 = "Ben de o yılın neden oraya yazıldığını bilmiyorum. Aslında, belki de biliyorum. Ama sana tavsiyem, fazla kafa yorma. Kitap faydalı, önemli olan da bu.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "Beklediğimden de umut verici, o yıl da herhalde bir baskı hatası... Her neyse. Çok teşekkür ederim, Kaptan!";
			link.l1 = "Rica ederim Gino. Hepsi senin.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "Bu kadar değil, Gino. Sana bu tabancayı göstermek istiyorum. Böyle bir şey daha önce gördün mü?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Ben silah ustası değilim, ama bir bakayım... Hayır, böyle bir şeyi hiç görmedim. Neden soruyorsun?";
			link.l1 = "Bu tabanca güçlü ve yıkıcı, ama kullanmak için özel mermiler gerekiyor. Başka hiçbir şey işe yaramaz. Ve daha fazla mermi nasıl yapılır, hiçbir fikrim yok. Bu yüzden tavsiyen için buraya geldim.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Bana örnek olarak gösterebileceğin en az bir elin var mı? Yoksa, üzgünüm ama sana yardımcı olamam.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Evet, biliyorum. Fişek iki bölümden oluşur: biri kurşunlu mermi, diğeri ise barutu ateşleyen şu parça.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "Böyle bir başarısızlık! Ne ayıp! Peki, belki daha fazlasını bulur ve sana getiririm.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("You have given a revolver's cartridge");
			Log_Info("You have given a capsule");
			PlaySound("interface\important_item.wav");
			dialog.text = "İlginç! Bu basit görünüyor, içinde barut var, üstten mermi giriyor ama biraz tuhaf duruyor. Ve şu 'şey'... hımm. Onsuz barut patlamaz, değil mi? Merak ettim... Bak Kaptan, bunların hepsini bana bırak: tabancayı ve fişekleri. Bir ay sonra yanıma uğra, çözmem için zamana ihtiyacım var.";
			link.l1 = "Harika! Nasıl çalıştığını çözmeye çalış, bu tabancayı gerçekten ateşlemek istiyorum.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "Asıl mesele, barutun patlamasını sağlayan bu maddenin neyden yapıldığını bulmak. Bu kitap işime yarayacak. Bu işin kökenine inmeye çalışacağım.";
			link.l1 = "Pekâlâ. Elveda, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Evet, tabancanın mermilerinin neyden yapıldığını çözdüm. Bana verdiğiniz kitaba hakkını teslim etmeliyim. O olmasaydı başaramazdım. Ama sizi uyarmalıyım Kaptan, bu silah için mermi ve kapsül yapmak kolay olmayacak.";
			link.l1 = "Kapsüller?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "Kapsül dediğin, tozu ateşleyen o 'şey'. Ama en baştan başlayalım. Hazır mısın?";
			link.l1 = "Evet! Seni çok dikkatli dinliyorum.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Öncelikle, özel bir mermi yapman gerekiyor. Sıradan mermiler işe yaramaz. Merminin konik bir şekli olmalı. Bunun için uygun bir kalıp bulmalısın, ben buna mermi kalıbı diyorum. Sıradan kurşun mermileri al, bir potada erit ve erimiş kurşunu mermi kalıbına dök. Döküm soğuyunca kalıptan çıkarıp hazır mermiyi alabilirsin.";
			link.l1 = "Ve böyle bir kurşun kalıbını nerede bulabilirim?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Bilmem, Kaptan. Ben simyacıyım, demirci değilim. Şu kurşunu örnek al, belki ne yapacağını anlarsın.";
			link.l1 = "Pekala. Devam et...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "O zaman barut için bir hazne yapmalısın. Kurşunu oraya yerleştiriyorsun. Senin için açık talimatlar yazdım. Dikkatlice oku ve dene bakalım.";
			link.l1 = "İyi...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Şimdi kapsülleri yapmamız gerekiyor. Çok ince bir bakır levhaya ihtiyacın olacak – bunu bakır külçesinden kendin yap. İçine mermilerle aynı boyda daireler oy. Sonra balmumu kullanarak içine fulminatlı gümüş yerleştir.";
			link.l1 = "Fulminan gümüş mü? O da ne?";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Ben de bundan haberdar değildim, sırrı senin kitabından öğrendim. Gümüş, ispirto ve nitrik asitten yapılabilen beyaz bir toz bu. Sürtünme ya da sarsıntıyla kolayca patlıyor, bu yüzden tabancanın barutunu ateşlemek için çok işe yarıyor. Hoş bir şey değil, tarifi bulana kadar denemelerimde iki kez patladı.";
			link.l1 = "Bu kitabın yanımda olması büyük şanstı!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Be very careful, this stuff is explosive as hell! I could make some myself, but storing fulminating silver is too dangerous; it's vital that you put it in the capsules right after it's made. I can't craft copper capsules, I'm no blacksmith, as I've told you before.";
			link.l1 = "Pekâlâ. Tarifini ver, kendim öğrenirim.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Rica ederim. Tarife tam olarak uy ve işlemlerin sırasına dikkat et, yoksa şişelerinle birlikte havaya uçarsın.";
			link.l1 = "Dikkatli olacağım.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Ayrıca, şu iki şişeyi de al. Bunda nitrik asit var, bunda ise ispirto. Yaklaşık 20 kapsülü dolduracak kadar fulminatlı gümüş yapabilirsin.";
			link.l1 = "Teşekkür ederim, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("You have received a flask of nitric acid");
			Log_Info("You have received a flask of spirit");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tabancanı ve örnek barutunu da al. İyi şanslar Kaptan, barut hazırlamada başarılar. Umarım sağ salim kalırsın.";
			link.l1 = "Kendimi korumak için elimden geleni yapacağım. Ve Gino, sana bir dahisin olduğunu söylemiş miydim?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Beni utandırıyorsunuz, Kaptan, ben ciddiyim...";
			link.l1 = "Pekala. Hoşça kal, Gino! Sen benim en iyi simyacım oldun!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Kaptan hakkında bana biraz daha anlatır mısın? Nereliymiş?";
			link.l1 = "Hiçbir fikrim yok. Kuzeyde bir yerde doğmuş olmasına rağmen, bazen ona Viking derlerdi.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Bir Viking! Evet, evet, hatırlıyorum, bunu bir tarih kitabında okumuştum. Bir gord, özgür bir jarl'ın tahkimli yerleşimidir.";
			link.l1 = "Özgür bir jarl mı? O da kimmiş?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Kuzeylilerin bir prensi bu. Yüzyıllar önce özgür jarllar ve savaşçıları, drakkar adı verilen gemileriyle Avrupa'yı yağmalar ve talan ederdi. Onlara korsan da diyebilirsin sanırım. Gordlar ise onların üsleri ve evleriydi; dinlendikleri, çiftçilik yaptıkları ve şölenler düzenledikleri yerler.";
			link.l1 = "Anladım. Demek bu gord onun korsan sığınağı... Teşekkürler, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Ateş ve sayıklamalar mı diyorsunuz? Bu ilginç. Onu hemen buraya getirin! Elimden geleni yapacağım. Ama durumu çok ağırsa size bir şey vaat edemem... O sizin subayınız mı?";
			link.l1 = "Hayır, Tanrıya şükür, değil. Gino, bak, kim olduğunu sorma, sadece elinden geleni yap, bu benim için gerçekten çok önemli!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Pekala, onu eve, odana götür. Ben bazı karışımlar hazırlayacağım... belki bu kök işe yarar...";
			link.l1 = "Hemen şimdi onu buraya getireceğim!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "O halde onu bir an önce bulmaya çalış, ilaç olmadan onu iyileştiremeyeceğim ve acele etmezsen çok geç olabilir.";
			link.l1 = "Pekâlâ, parayı bulacağım.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Harika, Kaptan. Şimdi bazı karışımlar hazırlayacağım ve size hastamı yalnız bırakmanızı tavsiye ederim. Yarın tekrar gelin.";
			link.l1 = "Pekâlâ, Gino. Karışımlarına ve dahiliğine güveniyorum.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Bence iki hafta içinde iyi olacak. Dans edebileceğine söz veremem ama en azından kendi ayakları üzerinde durabilecek, orası kesin.";
			link.l1 = "Lanet olsun, iki haftam yok! En kısa zamanda... yelken açmam gerek!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Captain, I am not a mage, but I can assure you that the man is too weak for now. I am not sure he will survive even a few days on the ship; you can't move him!";
			link.l1 = "Peki, peki, ama iki hafta—hayır, bir hafta bile fazla!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Üç gün... evet, sanırım üç gün sonra yelken açmayı deneyebilirsiniz, ama onun bakıma ve ilaca ihtiyacı olacak ve sık sık durmanız gerekecek.";
			link.l1 = "Bir doktorum var, onunla ilgilenecek. Üç gün sonra döneceğim ve onu alacağız, elimden gelen en fazlası bu. Hemen yola çıkmamız lazım, duraklarla bile olsa... evet, bir de Gino, sen tam bir dahisin!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Teşekkür ederim, Kaptan. Üç gün sonra arkadaşınızı almak için tekrar gelin, ama o zamana kadar onu rahatsız etmeyin. Tam anlamıyla dinlenmeye ihtiyacı var.";
			link.l1 = "Pekala, anladım. Onu üç gün içinde getireceğim.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Durumu iyi, ama ilerleme yavaş. Henüz alınamaz.";
			link.l1 = "Evet - evet, Gino, hatırlıyorum. Üç gün...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Durumu kötüleşmedi, ama pek de iyileşmedi. Hâlâ kendinde değil, nerede olduğunu ya da neden burada bulunduğunu anlamıyor, gerçi bu onu pek rahatsız ediyor gibi de görünmüyor. Ateşi de var, bu yüzden onu şimdi gemiye almak iyi bir fikir mi, emin değilim.";
			link.l1 = "Daha fazla bekleyemem, zaten burada fazlasıyla oyalandık. Ona yolculukta yardımcı olacak karışımlarını topla, gidiyoruz. Umarım bu herif idamını görecek kadar uzun süre hayatta kalacak kadar güçlüdür...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Dur bir dakika, Kaptan! Ben idama mahkûm olanlara mı bakıyordum? Ne oluyor burada? Burada inanılmaz bir iş yapıldı, kuru barut hazırlamanın ne kadar zor olduğunu biliyor musun...";
			link.l1 = "Gino, bunu bilmen gerekmiyordu. Çok fazla endişelenme, o bir korsan ve kendi türünün en ünlülerinden biri. Onu mümkün olan en kısa sürede Şirket'in yetkilileriyle görüşmesi için Curaçao'ya götürmem gerekiyor. Nokta.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Pekala, sen daha iyi bilirsin. O zaman korsan... Curaçao. Her neyse, ama beni dinle, çoğu zaman uyuyor olacak, fakat geminin sallanması ve bunaltıcı sıcak tüm süreci geciktirebilir. Birkaç gün yol aldıktan sonra durup... mahkumunu karaya çıkartıp dinlendirmeni tavsiye ederim. Yoksa Curaçao'da bir ceset asıyor olabilirsin... ";
			link.l1 = "Pekala, bunu yapacağım. Martinique gayet uygun, Curaçao'ya neredeyse yarı yolda. Umarım rüzgar lehimize olur. Onu şimdi alıp yola çıkacağız. Tekrar teşekkürler, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Hoş geldiniz, Kaptan. Unutmayın, dört gününüz var—yani, aslında beş, ama daha fazlası değil. Ve son bir şey... bilirsiniz, genelde insanları tedavi ediyorum çünkü onların tedavimden sonra asılmalarını istemiyorum. Bir doktor hastalarından, kim olurlarsa olsunlar, sorumludur. Ve kendimi gerçekten kötü hissediyorum...";
			link.l1 = "Seni bu işlerin içine sürüklediğim için üzgünüm, ama sensiz hiçbir şansımız yoktu. Şimdi yelken açmalıyız, yoksa Portekizli adamlar patronlarını karşılamak için kapımızda toplanacaklar.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "İlginç... Peki bana tam olarak nasıl yardım edebilirsin? Benim yardıma ihtiyacım yok, hem senden de bir şey istemedim...";
			link.l1 = "Ama buna ihtiyacın olacak. Önce beni dinle, sonra karar ver.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Tamamen seni dinliyorum.";
			link.l1 = "Son zamanlarda Santiago'daydım... Baba Vincento'yu ziyaret ettim. Kayıp sekreterini arıyordu, adı... Aman Tanrım, neden birdenbire bembeyaz oldun, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Sen... engizitörü gördün mü? O...";
			link.l1 = "Endişelenme, Gino. Onu sana teslim etmem söz konusu bile değil, emri bu olsa da: seni bulmamı ve ona götürmemi istedi. Itza halkından bir Hintli hakkında bazı bilgilere ihtiyacım var. Bana Tayasal'dan, hazinelerinden ve etrafındaki 'kötülükten' bahset.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Oldukça iyi bilgilendirildiğini görüyorum. Bunu sana Peder Vincento mu söyledi?";
			link.l1 = "Ondan biraz bilgi aldım, birazını da başkalarından öğrendim. Ama senin bakış açını da duymak isterim. Bir zamanlar onun sekreteriydin, yani sorgunun kaydını tutmuş olmalısın, öyle değil mi?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "O zavallı Hintliye neler yaptığını hayal bile edemezsin!.. O sorguyu aklıma getirdikçe tüylerim ürperiyor.";
			link.l1 = "Yine de, konuşalım bunu. O Kızılderili kimdi? Nasıl oldu da Peder Vincento'nun eline düştü?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "He was among the Indians of the Itza people who travelled from Tayasal in search of the Kukulcan Mask - an artifact of the ancient Maya god Kukulcan. Those Indians encountered a band of white adventurers led by Archibald Calhoun - a treasure hunter from Scotland. Only one Indian survived; his name was Ksatl Cha. He had three interesting items on him, I will tell you about them later.\Calhoun tried to force the prisoner to tell him about treasures, but he kept silent. So the Scot delivered him to Santiago, to Father Vincento, in exchange for permission to visit Spanish cities for a year. He knew that the inquisitor was very interested in all kinds of local mysteries and legends. Vincento made the Indian talk. He started talking a lot, he told us everything he knew, and the information we got out of him shocked the inquisitor himself.";
			link.l1 = "Yok artık? Onun Yüceliği'ni ne titretmiş olabilir ki?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Sana her şeyi sırayla anlatacağım. Yucatán ormanlarının derinliklerinde Tayasal adında eski bir Maya şehri var. Orada Maya soyundan gelen Itza halkı yaşıyor. Hayatlarını atalarının kurallarına ve geleneklerine göre sürdürmeye çalışıyorlar. Elbette, modern dünyanın halinden - yani beyaz adamın egemenliğinden - hiç hoşlanmıyorlar.\nEski güzel günlerin hayalini kuruyorlar. Ve şimdi en ilginç kısmına geliyoruz. Bir grup beyaz maceracı, tesadüfen Tayasal'a yaklaşmış ve Itza halkının büyük şefinin kızını kaçırmış. Bu neredeyse çeyrek asır önce olmuş.\nBu, bardağı taşıran son damla olmuş ve şef Kanek öfkeye kapılmış. Maya'ların en tehlikeli ve gizli ritüelini yapmaya karar vermiş: bir Hint tanrısını çağırarak beyaz fatihlerin tüm soyunu yok etmek...";
			link.l1 = "Hm... Demek Peder Vincento'nun bahsettiği iblis bu. Ama bu Hint tanrısı beyaz sömürgecilerle nasıl başa çıkacak? Bir ejderha gibi ortaya çıkıp hepsini yakacak mı?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Oh, "+pchar.name+", bırak bu ateş canavarı masallarını yaşlı ninelere! Aslında o kadar da haksız değilsin, ama bizim durumumuz çok daha zor ve ciddi. Hatta Tufan bile Avrupa'nın Yeni Dünya'ya yayılmasını durduramaz. Bir ölenin yerine on tane daha gelir. Kanek, Avrupalıların kolonileşme ihtimalini kökünden yok etmesi gerektiğini biliyordu.";
			link.l1 = "Pekâlâ, zaten oldu bile.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Doğru düşünüyorsunuz, Kaptan... Kanek'in ayininin amacı yalnızca yüce varlığı çağırmak değil, aynı zamanda bir uzay-zaman yarığı yaratmaktı.";
			link.l1 = "Ne?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Kadim Mayalar olağanüstü bir bilgiye sahipti, Kaptan. Kanek, zamanı kontrol etmeye yarayan bir ayinin tarifini bulmuş.";
			link.l1 = "Vay canına! İnanılmaz!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Dinle. Ritüelin nihai amacı, geçmişi değiştirip beyaz adamın Yeni Dünya'ya gelişini imkânsız kılmak. Bunu başarmak için, geçmişe birini gönderecekler; otoritesi, gücü ve insanların kaderini değiştirme yeteneği olan birini. Ama en önemlisi, böyle birinin modern bilgiye sahip olması gerekiyor.\nBir düşün, "+pchar.name+", Kristof Kolomb'un karavelleri, modern toplarla donanmış Hintli bir firkateyn ve kalyon filosuyla karşılaşsaydı ne olurdu? Ya beyaz askerlerin tüfeklerine ok ve mızraklarla değil de havan topları ve misket tüfekleriyle karşılık verilseydi?";
			link.l1 = "Sanırım Amerika kıtaları hiç keşfedilmemiş olurdu....";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Kesinlikle! Belki de bir Hintli 'Kolomb' Avrupa'yı keşfetmiş olurdu...";
			link.l1 = "İlginç, peki Kanek geçmişe kimi gönderecek? Çıplak savaşçılarından birini mi? Atalarına bir şey öğretebileceğinden şüpheliyim...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Gülme, Kaptan. Kanek yıllarını Maya tapınaklarında sadece yazılarını okuyarak geçirmedi. Bir Hint tanrısı insan suretinde geçmişe gönderilmeli...";
			link.l1 = "Gino, ne saçmalıyorsun? Yoksa sen....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Efendimizin Oğlu, İsa Mesih bile, insan suretinde dünyamıza geldi ve Kutsal Bakire Meryem’den doğdu...";
			link.l1 = "Tanrım, Gino... ciddi misin?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Elbette öyleyim. Ksatl Cha çok ikna ediciydi...";
			link.l1 = "Peki Kanek böyle 'soylu' bir görev için hangi tanrıyı seçti?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Bu ayin yalnızca bir Yüce Varlığı çağırmak içindi. Tüylü yılan, Quetzalcoatl, Kukulcan...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulcan mı?! Onun heykellerde yaşayan 'ruhuyla' karşılaşacak kadar düşüncesiz davrandım zaten. Şimdi anlıyorum... devam et!";
			else link.l1 = "Hm. İlginç. O ismi zaten Peder Vincento’dan duymuştum... devam et!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek decided to summon Kukulcan, since the Itza already possessed an ancient artifact of this god - the Mask of Kukulcan. Whoever holds the mask is able to pass through the portal, and only he will be accepted by the ancient Maya as a living god.\nThe priest performed the ritual, summoning Kukulcan to incarnate in the body of a mortal. He also created a time rift that drew several random people from the future into our era.\nThe purpose of this extraction was to endow Kukulcan's incarnation not only with the knowledge of our time, but also of the future. But something went wrong, and all those people arrived elsewhere, not in Tayasal. I have never met any of them.\nSeveral portals were created throughout the archipelago; they were meant to transport bearers of future knowledge and Itza agents across the region and to Tayasal. But these portals failed in their purpose—no one has been brought to Tayasal in the last 25 years...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "Tabii... Çünkü bu geçitler sadece yakalanan insanları birbirlerine aktarıyor. İnanılmaz!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "İlginç...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Şu geçitleri gördün mü? Söyle bana!";
			link.l1 = "Belki sonra, Gino... Şu an senin hikayeni daha çok merak ediyorum. Devam et!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Peder Vincento, sana anlattığım her şeyden haberdar. Tabii ki bu onu endişelendirdi. Eğer insan suretine bürünmüş Kukulcan, Maske ve topladığı tüm bilgilerle birlikte portalı bulursa... Zamanın sonu gelir. Kıyamet.\nGeçmiş değişirse - gelecek de değişir. Gerçekliğimiz değişecek, yok olacak, çözülecek. Sen ve ben belki hiç doğmayacağız. Ya da bambaşka olacağız. Kukulcan geçmişe ulaştığında - biz var olmaktan çıkacağız.";
			link.l1 = "Ve Kukulcan'ın enkarnasyonu kim?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Who knows. He might be anyone who was born a quarter of a century ago, when the ritual was conducted. In you, for example... just kidding. But we still have a chance. First, Kukulcan's incarnation is just a mortal person; he can drown, be stabbed, be shot, or die of fever. And in such a case, no apocalypse will ever happen.\nSecond, it is impossible to reach the past without the mask. Kanek stashed it very well—maybe too well, it seems. It might be that even the incarnated Kukulcan will fail to find it.";
			link.l1 = "Bana daha fazla anlat.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Some time after the ritual, a group of Spanish conquistadors almost reached Tayasal and nearly made it to the treasury. The Itza managed to kill all of them except one—a strong giant, seven feet tall.   Kanek was worried that the Mask could be stolen by any stranger, so he decided to protect the relic. He devised his own ritual, using the ancient Maya's knowledge. He took three items which he believed held the power of the white man: a dagger, which once belonged to Cortez himself, and a compass. He also used that dagger to carve out a piece of skin from the back of the captured Spanish giant as the third item. The man himself was sacrificed on the altar of Kukulcan. Three items were used in the ritual.   And from this ritual, a new island was born, in the open sea, not far from Yucatan. No one knows its location, but the Mask is stashed there. In order to find it, one must use the dagger, the compass, and the piece of skin. Besides, all items from the treasury are cursed; not a single one of them can leave the archipelago.   An attempt to do so will cause a storm which will drive the ship right onto the rocks of the island where the Mask is hidden. It is called Ksocheatem. Smart, isn't it?";
			link.l1 = "Belki de fazla zeki. Buna diyecek bir şey yok. Ama Ksatl Cha nasıl bu kadar iyi bilgi sahibi olmuş? Kanek’in böyle şeyleri sıradan savaşçılarla paylaştığına hiç inanmam...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Thing is, the current chief of the Itza, Urakan, son of Kanek, had told this warrior everything. He sent Ksatl Cha with a group of warriors to find the secret island and the Mask of Kukulcan. He had given him the Guardian of Truth to do that; it is the name of the three items together - the dagger, the compass, and the map made of human skin.";
			link.l1 = "Harita mı? Peki Urakan Maskeyi neden istedi? Geçmişi kendi başına değiştirmeye mi karar verdi?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Cildin üzerinde takımadaların hatları var, bu yüzden ona harita diyorlar. Urakan Maskeyi çok basit bir sebepten istiyordu – mevcut gerçekliği yok etmek ya da atalarının şanı uğruna kendi hayatını ve halkının hayatını feda etmek istemiyordu.\nBu yüzden Maskeyi ne pahasına olursa olsun yok etmeye kararlıydı. Ama Ksatl Cha, Calhoun tarafından ele geçirildi ve... işte hikâyenin gerisini biliyorsun. Ksocheatem'e asla ulaşamadı.";
			link.l1 = "Yani, Maskeyi bulup yok ederek dünyanın sonunu engellemek mümkün mü? Peki o... Gerçeğin Muhafızı şimdi nerede?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = " 'Şefin Pençesi' hançeri ve 'Yolun Oku' pusulası Calhoun'a bırakıldı, 'İki Yüzlü' deri harita ise hâlâ Engizisyon'un elinde bir yerlerde. Calhoun, haritayı mahkûmun ağzını kapatmak için bir tıkaç olarak kullandı. Bu eşyaların ne işe yaradığından haberi yoktu.";
			link.l1 = "Ne dedin az önce? 'Şefin Pençesi' mi? Kahretsin, bu hançer şu anda bende! Fadey, ağabeyime olan borcuna karşılık bana verdi! Bak istersen!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "İnanılmaz... Gerçekten öyle. Hatırlıyorum bunu.";
			link.l1 = "Gino, söyle bakalım, Peder Vincento senin hikayen hakkında tam olarak ne biliyor?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Her şey, sadece Hakikatin Muhafızı'na dair bilgiler ve Kukulcan'ın Maskesi'nin saklandığı gizli adanın yerini nasıl ortaya çıkaracağı hariç. Ksatl Cha, bunu bana yalnız kaldığımızda anlattı, acılarını dindirmek için ona zehirli karışımı vermeden hemen önce. Yüzünde bir gülümsemeyle öldü.\nYaptıklarımdan sonra Santiago'da kalmam elbette mümkün değildi. Engizisyoncu için önemli ve tehlikeli bir tanık haline geldiğimden ciddi şüphelerim vardı. Peder Vincento ne isterse, bedeli ne olursa olsun elde eder. Ksatl Cha ona Tayasal'daki hazineden bahsetmişti.";
			link.l1 = "Bu hazineleri zaten Miguel Dichoso adında bir maceracı bulmuş. Onu duydun mu?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Hayır.   Peki şimdi nerede, hazineleriyle birlikte?";
			link.l1 = "Kendimi tanımak istiyorum. Bu yüzden sana geldim, o Hint altınını arıyorum. Dichoso hazineleri Avrupa'ya götürdü ve onlarla birlikte ortadan kayboldu.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Sana hazinelerin ve bizzat Dichoso'nun nerede olduğunu söyleyeceğim.";
			link.l1 = "Gino, beni şaşırtıyorsun. Bunu nereden biliyorsun?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Hikayemden bunu kendin anlayabilirsin, Kaptan. Tayasal hazineleri lanetliydi - takımadalardan tek bir parça bile dışarı çıkarılamaz. Herhangi bir gemi...";
			link.l1 = "... fırtınaya yakalanıp Kukulcan'ın Maskesi'nin saklandığı adaya savrulacağım! Körmüşüm, ama artık görüyorum. Görünen o ki, Ksocheatem'i, hazineleri ve Maskeyi bulacak kadar çok şey biliyorum!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Dünyayı kurtarmak ister misin, Kaptan?";
			link.l1 = "Kayıp kardeşimi bulmak istiyorum... Gino, Hakikat Muhafızı'na adanın yerini nasıl açıklatabilirim? Bunu bildiğini söylemiştin!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Yöntemi biliyorum, ama ayrıntıları bilmiyorum. Koruyucu'nun tüm parçalarını bulmadan sana yardımcı olamam.";
			link.l1 = "Hm. Hançer zaten bizde. Geriye sadece pusula ve harita kaldı. Pusula Calhoun’da, harita ise Peder Vincento’da...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Engizitöre geri mi döneceksin? Ama nasıl rapor vereceksin...";
			link.l1 = "Babam Vincento'yu öldüğüne inandırmam gerekiyor, Gino. Ancak o zaman aramayı bırakır. Diyelim ki beni görünce aniden bir felç geçirdin. Ölümüne dair kanıt olarak kullanabileceğim bir eşya vermelisin bana.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento kalp krizi hikayesine inanmaz, ama ona badem kokulu bir zehir içerek intihar ettiğimi söylersen sana inanır. Ona almanağımı ver, ondan hiç ayrılmadığımı bilir.";
			link.l1 = "Pekâlâ. Çünkü engizisyon görevlisiyle o bağlantıya ihtiyacım var. Muhtemelen işlerimiz hakkında çok şey biliyor.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Baba Vincento'ya dikkat et. O, kaplan kadar tehlikelidir ve kendi oyununu oynar. Ne hazinesini ne de şöhretini seninle paylaşmaz.";
			link.l1 = "I understand that. Fine, Gino, give me your almanac and try to remember what the Indian told you about the Guardian of Truth, because I want to piece it together. I need to find Ksocheatem; I am sure that I will find not only the mask and the treasures there, but also my dear brother.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Al bunu. İyi şanslar, Kaptan!";
			link.l1 = "Elveda demiyorum, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("You have received an almanac");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Zor muydu, Kaptan?";
			link.l1 = "Bu konuyu konuşmayalım... Bu eşyaları elde etmek için çok fazla insan öldü. Hem de fazlasıyla. Görünen o ki, gizemli Ksocheatem'i bulmak için hevesli olan tek kişi ben değilim. ";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Hayal edebiliyorum... Bu arada, Peder Vincento nasıl? Onunla düzenli olarak görüşüyor musun?";
			link.l1 = "Şimdiye kadar öyleydi, ama artık buna gerek kalmadığını düşünüyorum. Artık Hakikatin Muhafızı'nın tüm parçaları elimde, yani Ksocheatem'in yerinin anahtarı bende. Nedense, başarımı Ekselanslarına bildirmek için hiç acelem yok.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Dikkatli ol, "+pchar.name+"   Baba Vincento'nun yüzlerce gözü ve eli var. Çok uzun elleri...";
			link.l1 = "Son birkaç ayda çok şey yaşadım ve bu noktada artık ne Peder Vincento'dan ne de onun gözlerinden ve ellerinden korkuyorum. Her neyse. Artık Koruyucu'nun parçalarını kullanarak Ksocheatem'i bulmamızın zamanı geldi. Bunu nasıl yapacağımızı biliyor musun? ";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Pek sayılmaz. Ksatl Cha oldukça belirsizdi. Sanırım o Kızılderili Muhafız'ı nasıl çalıştıracağını tam olarak bilmiyordu. Parçaları bana bırak, ben çözmeye çalışırım. İki gün sonra yanıma gel, belki o zamana kadar bu bilmeceyi çözmüş olurum.";
			link.l1 = "Peki, Gino. Sana güveniyorum. Al, bunlar senin.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Onların güvende ve sapasağlam kalacağından emin olabilirsin.";
			link.l1 = "Bundan şüphem yok. Neyse, şimdilik seni rahatsız etmeyeyim Gino. Araştırmalarında bol şans!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Kısmen. Yani, elimde bir şeyler var ama hepsini nasıl gerçeğe dönüştüreceğimi bilmiyorum. Gel, bu bulmacayı birlikte çözmeye çalışalım.";
			link.l1 = "Hadi deneyelim! Fikirlerini söyle.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha şöyle dedi: 'Şefin Pençesi haritanın kendini göstermesini sağlayacak. Yolun Oku ise görünümlerin yönünü gösterecek.'";
			link.l1 = "Ve sen neler başardın?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Haritanın kendini nasıl 'açığa çıkardığını' çözdüm. İki Yüzlüler Haritası'na baktın mı?";
			link.l1 = "Hm. Ve olağan dışı bir şey var mıydı? Takımadanın belirsiz hatları gibi...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Al bunu ve bir daha bak. Dikkatli ol.";
			link.l1 = "Pekâlâ, madem ısrar ediyorsun, öyle yapalım.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Haritaya bakmadın, "+pchar.name+"...";
			link.l1 = "Evet, evet, şimdi yapacağım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Gördüm. Yeni bir şey göremedim. Sadece adaların ve ana karanın silik şekilleri vardı. Orada ne görmem gerekiyordu ki?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Bir saniye bekle. Şimdi bu haritanın kendini göstermesini sağlamalısın. Hançeri al ve kenarıyla haritaya hafifçe dokun. Bastırma, zarar vermemeliyiz. Hançeri al. Ve dikkatlice izle!";
			link.l1 = "İlginç! Bakalım...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Peki, şimdi bir fark görebiliyor musun?";
			link.l1 = "Evet. Haritaya hançerle dokunduğunda iki kafatası işareti beliriyor ve bunlar her zaman aynı yerlerde oluyor...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Aynı iki yerde, "+pchar.name+"! İşte bu yüzden ona İki Görünüşün Haritası denmiş!";
			link.l1 = "Ve bu ne anlama geliyor?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Bence çok şey... Ama sırada daha fazla bilmece var. Sanırım bu kafatasları, Ksatl Cha'nın bahsettiği hayaletler. O halde pusula, Ksocheatem'e giden doğru yolu onlardan göstermeli. Pusulayı gördün mü, "+pchar.name+"?";
			link.l1 = "Yes. It looks like an ordinary naval compass, but it behaves strangely; its needle twitches in different directions or starts spinning wildly.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Pusulayı kafataslarının üzerine koymanın ibresini durdurup haritada net bir yön göstereceğini düşündüm. Bunu yapmak için pusulayı önce bir kafatasına, sonra diğerine yerleştirdim ve aynı anda haritaya hançerle dokundum.";
			link.l1 = "Ve?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Boşuna. Pusulanın davranışı değişmedi. İbre hâlâ deli gibi dönüyor. Sanırım bir şeyi yanlış yapıyorum. Ya da belki de Ksatl Cha'nın sözlerini yanlış anladım.";
			link.l1 = "Yani hançer ve harita işe yarıyor, ama pusula çalışmıyor mu?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "Yolun Oku kesinlikle çalışır durumda olmalı, sadece onu nasıl çalıştıracağımızı henüz bilmiyoruz. "+pchar.name+",  takımadaların coğrafyasını benden daha iyi biliyorsun... Söylesene, iki yüzlü harita hangi yerleri gösteriyor?";
			link.l1 = "Bir saniye! (şöyle bir bakayım)... Hımm, soldaki topraklar batı Main'e ait. Sağdaki ise Dominika adasına benziyor. Öyle bir şey.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "Ve bana söyle: O yerlerde... dikkate değer bir şey var mı?";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Ben de tam emin değilim... Yani, özel bir şey mi?";
			link.l1 = "Gino, bilmecelerle konuşma. Açıkça anlat.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Sanırım bu kafatasları bize gerçek yerleri gösteriyor. Yolun Oku, haritanın üzerindeki resimlerde işe yaramıyor. Belki haritanın ortaya çıkardığı gerçek coğrafi özelliklerin yakınında işe yarar?";
			link.l1 = "Gino, sen bir dahisin! Batı Ana, Dominika mı? Kafatasları tam yerleri göstermek için fazla büyük.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+", şöyle yapalım: Bana takımadanın kağıt haritasını getir, İki Yüzlüler haritasıyla birleştir ve görünümleri çarpılarla işaretle. Belki bu seni bazı tahminlere götürür?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Takımadaların bu eski haritası bende var.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Takımadaların bu güzel haritası bende var.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Takımadaların bu harika bir haritası var elimde.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Anlaştık. Haritayı getireceğim ve devam edeceğiz...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Aman, hadi ama, "+pchar.name+"! Bu Kolomb zamanından kalma parşömen, deri haritadan pek de iyi değil. Eminim dünyada bundan daha iyi bir şey vardır. Bana başka bir harita getir, daha yeni bir tane!";
			link.l1 = "Pekâlâ...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Harika! Şimdi üzerinde ortaya çıkış noktalarını işaretle. Bu, varsayımlar yürütmemizi kolaylaştıracak.";
			link.l1 = "Bir saniye, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "Böyle harika bir haritayı işaretlerle mahvetmeye hiç niyetimiz yok. Zaten sana da lazım olacak, "+pchar.name+" . Bana biraz daha mütevazı bir harita getir!";
			link.l1 = "Peki...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Bana takımadaların haritasını getirdin mi, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Takımadaların bu eski haritası bende var.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Takımadaların bu güzel haritası bende var.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Takımadaların bu harika bir haritası var elimde.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Henüz değil, ama çoktan sipariş ettim. Yakında elimde olacak ve devam edeceğiz...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Tamam... İşaretlemeleri yaptım, ama bilgiler hâlâ tam olarak kesin değil. İlk yer Blueweld’in kuzeybatısında bir yerde. İkincisi ise Dominica adasının tam ortasında.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Bir fikrin var mı?";
			link.l1 = "Hayır. Ama bence Arrow of the Way'i oraya götürüp nasıl davrandığını gözlemlemeliyiz. Tabii, samanlıkta iğne aramak gibi olacak, ama zaten daha iyi bir fikrimiz yok.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Sana katılıyorum, "+pchar.name+". Benim seninle birlikte denize açılmama izin verir misin?";
			link.l1 = "Varsayımlarını test etmeye hevesli misin? Seni gemimin güvertesinde görmek benim için bir onur olurdu, Gino. Eşyalarını topla!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "Uzun sürmez. Birkaç saat içinde hazır olurum. Al, işte Yolun Oku.";
			link.l1 = "Hoş geldin!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Evet, evet, "+pchar.name+", Kendimi hazırlıyorum. Yakında hazır olacağım.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "Ee, ne olmuş yani, "+pchar.name+", aramalarımızda şansımız yaver gidiyor mu?";
			link.l1 = "Haklıydık. İşte bu. Hint putu onun biçimlerinden biri.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "Oh! Bu, insanları Tayasal'a ışınladığı söylenen o putlardan biri olmalı! Sana onlardan bahsetmiştim, hatırlıyor musun? Peki, Yolun Oku nereye işaret ediyor?";
			link.l1 = "Kuzeybatıyı gösteriyor. Yönü haritada işaretledim. Çizilen çizgi neredeyse tüm Karayip Denizi'ni geçiyor. Ksocheatem'i bulmak için Dominika'da başka bir ortaya çıkış noktası bulmamız gerekecek.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Eminim orada başka bir put daha bulacağız... hipotezime katılıyor musun, "+pchar.name+"?";
			link.l1 = "Evet, Gino. Şimdi vakit kaybetmeyelim ve aramaya başlayalım.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "Ee, ne olmuş yani, "+pchar.name+", ilginç bir şey bulabildin mi?";
			link.l1 = "Haklıydık. İşte bu. Hint putu, onun biçimlerinden biri.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "Ah! Bu, insanları Tayasal'a ışınladığı söylenen o putlardan biri olmalı! Sana onlardan bahsetmiştim, hatırlıyor musun? Peki, Yolun Oku hangi yöne işaret ediyor?";
			link.l1 = "Kuzeybatı. Yönü haritada işaretledim. Çizilen hat neredeyse tüm Karayip Denizi’ni geçiyor. Ksocheatem’i bulmak için Ana Kara’da başka bir çıkış noktası bulmamız gerekecek.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "Ee, ne olmuş yani, "+pchar.name+", ikinci putu buldun mu?";
			link.l1 = "Yes. I have drawn the direction shown by the Arrow of the Way. Now we know the location of Ksocheatem; it's not the exact spot, but we know where to search! I will search the whole area where the lines cross, and I will find that damn island!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "I am glad to hear such enthusiasm in your voice. But we must prepare well for the upcoming expedition; it is unknown what we will face there. I doubt we will receive a warm welcome...";
			link.l1 = "Özel bir şey için mi endişeleniyorsun, yoksa sadece kaygılarını mı dile getiriyorsun?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Bir düşün, "+pchar.name+".. Ksocheatem was created by Mayan magic performed by Kanek. It is not a natural formation and it possesses evil and destructive powers. It is unknown what awaits us there; I doubt we will find sunshine, peaceful seas, whores, or a calm wind there.";
			link.l1 = "Pekala, Gino. Sözlerini dikkate alacağım ve sefere hazırlanacağım. Gemimi hazırlayacağım, iksirlerle mühimmatı da halledeceğim...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Çok akıllıca bir karar. Peki, gemiye geri dönelim mi?";
			link.l1 = "Tabii! Hadi gidelim!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Vardık, "+pchar.name+"! Ah, rüzgar uluyor!";
			link.l1 = "Evet Gino, haklıydın, bizi karşılayacak bir güneş ışığı yok... Fahişe de göremiyorum. Aslında, burada bizi neyin beklediği de belli değil.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Yani, Kaptan, karaya çıkmak için ne kötü bir yer seçmişsiniz! Her yerde kayalar ve uçurumlar var! Buradan adanın içlerine nasıl gideceksiniz peki?";
			link.l1 = "Bu lanet fırtına yüzünden bu adada yanaşacak başka uygun bir koy göremedim! Neyse, hiç yoktan iyidir. Şu kayaların arasında yolumu bulurum, daha beterlerini yaşadım. Sakin ol dostum!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Bu adadan hoşlanmıyorum, "+pchar.name+"! Çok ürkütücü. Ve bu fırtına kesinlikle adaya bağlı. Burası mahvolmuş, orası kesin!";
			link.l1 = "Ben de burayı pek sevmiyorum, Gino! Ama bu ada gerçekten var, demek ki Kukulcan'ın hikayesi doğru. Eğer Maskeyle Tayasal'a ulaşmayı başarırsa, hepimiz tehlikede olacağız...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Maskeyi bulmaya çalış, Kaptan! O, dünyadaki tüm hazinelerden daha önemli! Burada bir yerde olmalı! Onu ele geçirirsek, Kukulcan'ın planlarını bozacak ve geçmişi değiştirmesine izin vermeyeceğiz!";
			link.l1 = "Ve bu maskenin nasıl göründüğünü biliyor musun?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Hiçbir fikrim yok! Ama bence görünce tanırsın, eski bir Hint eseri, başka bir şeyle karıştırmak imkânsız!";
			link.l1 = "Anladım. Gözümü dört açarım! Tamam Gino, gemiye dön! Adayı dolaşmana gerek yok, senin kafan riske atılamayacak kadar değerli!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Yalan söylemeyeceğim, Kaptan, iyi bir dövüşçü değilim ve burada kendimi rahat hissetmiyorum. Bir tavsiye ister misiniz? Guardian'ın her bir parçası bu adanın büyüsüyle bağlantılı. Ksatl Cha hançerin buradaki yerliler üzerinde bir gücü olduğunu söyledi, ama ne demek istediğini bilmiyorum.   Gemide kalacağım. Yardımım gerekirse beni orada bulabilirsin.";
			link.l1 = "Güzel. Ve şimdi bana şans dile, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Bol şans, "+pchar.name+"! Tanrı seni korusun ve kutsasın!";
			link.l1 = "...";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Nasıl gidiyor, "+pchar.name+" ? Bir tavsiyeye mi ihtiyacın var? ";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Bu lanet ada ölülerle dolu, şu kahrolası iskeletler de şaşırtıcı derecede dayanıklı. Onlarla nasıl savaşacağımı hiç bilmiyorum.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Eğer çatallaşmada sola gidersen eninde sonunda mağaraya varırsın. Ama ben nereye gitmeliyim? Korkarım mağara çıkmaz bir yol...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Islak mağaraya girmeyi başardım, su altı kısmına dalabilirsin. Ama oradan bir çıkış göremedim...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Eğer çatallaşmada sola gidersen, mağaraya varırsın. Ama sonra nereye gitmeliyim? Korkarım mağara çıkmaz bir yol...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "Büyük mağarada su basmış bölüme dalabileceğin bir yer var. Ama oradan çıkış yok gibi görünüyor...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Şimdilik her şey yolunda, Gino, iyiyim.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha mentioned the Chief's Claw. Try to use it against the skeletons; the Indian said that this dagger holds power over the inhabitants of Ksocheatem.";
			link.l1 = "Kesinlikle deneyeceğim!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "Ve bu mağara nasıl görünüyor?";
			link.l1 = "Şey, kayada küçük bir mağara var, nemli, ve dibinde su tıpkı dalga gibi sallanıyor...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Eğer su dalgalanıyorsa, o zaman mağara mutlaka denizle bir bağlantısı var ve burası çıkmaz olamaz. Bir geçit ara, mutlaka bir yerde olmalı.";
			link.l1 = "Yoldayım...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Eğer ana mağaradan su basmış mağaraya bir yol varsa ve ana mağarada su dalgalar gibi hareket ediyorsa, o zaman su basmış mağarada ikinci bir geçit var demektir. Daha dikkatli araştır, ama dikkatli ol yoksa boğulursun.";
			link.l1 = "Dalmaya gidiyorum...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "Ve bu mağara nasıl görünüyor?";
			link.l1 = "Pekala, oldukça büyük, birkaç mağarası var, nemli ve içinde durgun su bulunan küçük bir delik var...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Eğer su hareketsizse, o zaman mağaranın denizle bağlantısı yoktur ve burası bir çıkmaz olabilir.";
			link.l1 = "Ben de aynı şeyi düşündüm. Orada uzun zamandır arıyorum ve sadece bir giriş var, o da aynı zamanda çıkış...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Eğer mağaradaki su hâlâ durgunsa, belki de haklısın. Biraz daha ara, ama bir şey bulamazsan üzülme. Muhtemelen burası çıkmaz bir yol.";
			link.l1 = "Anladım...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", İspanyol gemileri peşimizde! Şimdi konuşmak için en uygun zaman değil!";
			link.l1 = "Evet, tabii...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Mutlu gözlerin aradığını bulduğunu söylüyor bana.";
			link.l1 = "Evet. Miguel Dichoso'nun hazineleri ve Kukulcan'ın Maskesi. Artık onun enkarnasyonu asla geleceği değiştiremeyecek!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "İnanılmaz! Sen bir kahramansın, "+pchar.name+"...";
			link.l1 = "Gino, Kukulcan'ı durdurmak için bunun yeterli olduğuna emin misin?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Ksatl Cha'ya göre öyle. Hem de Urakan'dan alıntı yapıyordu. Bütün bu karmaşayı başlatan babası Kanek'ti. Şüphen var mı?";
			link.l1 = "Körfezde beni geçmişten bir misafir karşıladı – Alonso de Maldonado. Kanek Gerçeğin Muhafızını yaratmak için ritüel yaptığında Tayasal'daydı. Uzay-zaman yarığına sürüklendi ama hayatta kaldı... Bugüne dek.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Dünyamızı tamamen korumak için portalı kapatmam gerektiğini söyledi. Bunu yapmak için de Tayasal’daki bir sunakta Maskeyi yok etmem gerekiyor.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "Ve Tayasal'a mı gidiyorsun? Bu tam anlamıyla delilik! "+pchar.name+", maskeyi aldın ve Kukulcan'ın enkarnasyonu artık hiçbir şey yapamayacak! Kanek de bundan emin! Bu yüzden Urakan, Ksatl Cha'yı Ksocheatem'i bulması için gönderdi - Maskeyi ele geçirip yok etmek için.";
			link.l1 = "Ya bu Urakan Tayasal'da maskeyi yok etmeyi planlıyorsa?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+"Şimdiye kadar Tayasal'dan sağ çıkmayı başaran tek kişi Miguel Dichoso oldu. Maldonado da var ama o istisnaydı. Kukulcan'ın enkarnasyonu geçmişe dönse bile, eski Mayalar tarafından öldürülür!";
			link.l1 = "Ya onu öldürmezler de tanırlarsa?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Yani, Tayasal'a bir sefer mi planlıyorsun?";
			link.l1 = "Bilmiyorum, Gino. Gerçekten bilmiyorum...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "O zaman bir düşün, neden böyle bir şey yapasın? Benim fikrimi duydun. Artık karar senin..."+pchar.name+", beni St. John's'a götürür müsün?";
			link.l1 = "Tabii Gino. Bir an önce yelken açalım. Bu berbat adadan bıktım artık.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Yakında eve dönecek miyiz, "+pchar.name+"? Şişelerimi ve tüplerimi gerçekten özledim...";
			link.l1 = "Evet, evet, Gino, yakında Antigua'da olacağız.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Nihayet geri döndüğümüze çok sevindim! Siz denizciler bu kadar zamanı gemilerde nasıl geçiriyorsunuz, aklım almıyor...";
			link.l1 = "Bu bir alışkanlık meselesi, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Yatakta uzanacağım, karada ayaklarım yere basacak, büyük bir keyifle... Umarım, "+pchar.name+", Tayasal'ı ziyaret etmeyi aklından bile geçirmemiş olman mı?";
			link.l1 = "Henüz bilmiyorum, Gino. Açıkçası, hâlâ emin değilim.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Kukulcan'ın maskesini yok edin ve endişesiz yaşayın, Kaptan. İsterseniz, elimdeki en güçlü asitte maskeyi eritip yok edebiliriz. Böyle bir mesele için size kin tutacak değilim.";
			link.l1 = "Biliyor musun, biraz bekleyeceğim. Onu yok etmek için her zaman vaktimiz olacak.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "Karar senin. Eğer bu dünyayı bu eserden kurtarmaya karar verirsen, bana gel. Harika bir yolculuk için minnettarlığımı sunarım, Kaptan!";
			link.l1 = "Her zaman, Gino. Görüşürüz!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen bir "+GetSexPhrase("Hırsız, beyefendi! Muhafızlar, yakalayın onu","Hırsız, kız! Muhafızlar, yakalayın onu ")+"!!!","Şuna bak! Ben dalıp gitmişken, sen de sandığımı karıştırmaya kalktın! Hırsız! Yakalayın şu hırsızı!!!","Gardiyanlar! Soygun! Hırsızı yakalayın!!!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

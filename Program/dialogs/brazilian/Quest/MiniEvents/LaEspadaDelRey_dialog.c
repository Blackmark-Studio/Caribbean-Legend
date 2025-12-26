void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Ei, rapaz! Você parece um marinheiro valente, e aposto que sabe se virar numa briga. Me ajudaria com uma pequena incursão em algum lugar, hein?";
			}
			else
			{
				dialog.text = "Oi, linda! Dá pra ver que você não é do tipo tímida se veio até aqui. Que tal me ajudar com uma pequena invasão em algum lugar, hein?";
			}
			link.l1 = "Suponho que você seja o velho procurando um guia para o navio antigo?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Então, os boatos viajam mais rápido que o vento. Sim, sou eu. Gonzalo Peralta – o único que ainda está vivo do naufrágio de 'La Espada del Rey.'";
			link.l1 = "E eu sou um capitão "+GetFullName(pchar)+". Quer dar mais uma olhada na sua embarcação?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Sim. Veja, ultimamente tenho sido atormentado pelo mesmo pesadelo, noite após noite. Mas isso nem é o pior... Acredite se quiser, toda manhã, assim que o pesadelo termina, eu acordo e... tem um maldito esqueleto parado bem na minha frente...";
			link.l1 = "Disseram que você conta essa fantasia para todo mundo.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Uma fantasia? Heh... Quem me dera fosse só isso. Alguns meses atrás, eu levava uma vida tranquila, como qualquer velho marinheiro aposentado deveria. Mas agora aquele saco de ossos aparece toda manhã, fica me encarando, solta um grito de gelar o sangue... maldição, até um contramestre ficaria apavorado... e então ele parte pra cima, pronto pra lutar. E sabe de uma coisa? Cada vez, os ataques dele ficam mais violentos. É justamente por isso que quero chegar ao navio o quanto antes—não consigo me livrar da sensação de que tem algo lá que eu preciso encontrar.";
			link.l1 = "Hmm... Que situação interessante. E o que você espera encontrar lá depois de tanto tempo?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Eu não sei, Capitão, simplesmente não sei... Mas sinto uma atração por aquele navio, como um velho barco em meio à tempestade. Meu sonho, aquele esqueleto, e essa sensação estranha... Pelo mar, de algum jeito, tudo isso está ligado. Só não consigo entender como.";
			link.l1 = "O que exatamente acontece no seu sonho? Isso tem alguma ligação com os nativos?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Então, você tem visões à noite e luta com um esqueleto de manhã? Talvez não seja o navio, talvez você só precise procurar um médico. Não vou alimentar sua imaginação fértil. Vá procurar outro tolo pra acreditar nessas bobagens.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Conectado? Pode apostar que sim, droga... Nesse sonho, estou com minha tripulação morta a bordo do 'La Espada del Rey'. Estamos... saqueando vilarejos caribes em Hispaniola, matando todos que aparecem no nosso caminho—homens, mulheres, crianças. Aqueles que revidam, e até os que caem de joelhos, implorando por misericórdia. Queimamos os povoados deles um após o outro. As flechas e tacapes dos índios contra nós são como uma tartana furada contra uma galé de guerra. Os caribes, desesperados, imploram por uma trégua, e então...";
			link.l1 = "Meu Deus! Então você participou de toda essa baderna? Você não precisa de ajuda, precisa é de uma corda no pescoço!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "Não! Não, droga, isso não é verdade, você entende?! Eu não faço ideia de por que estou sonhando com tudo isso... mas juro por tudo que é sagrado, nem eu nem minha tripulação jamais participamos de tais atrocidades!";
			link.l1 = "É bom que isso seja verdade. Continue.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Os caribes pediram negociações, e o capitão concordou. Ele convidou todos eles para uma daquelas cabanas que tínhamos tomado. Os chefes vieram — pelo menos duas dezenas, liderados por sua rainha, Anacaona. Mas o próprio capitão não entrou... nenhum de nós entrou. Assim que o último chefe entrou, a porta foi trancada com vigas. E então... maldição... eles atearam fogo. Só a rainha foi poupada, mas não por muito tempo. Fizeram ela assistir enquanto seu povo queimava vivo... E depois a enforcaram numa árvore.";
			link.l1 = "E isso acontece toda noite? O mesmo sonho, de novo e de novo? Sabe, eu não me surpreenderia se, no fim das contas, esse esqueleto fosse só fruto da sua imaginação febril...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Isso não é tudo. Os caribes sobreviventes fugiram para Cuba, encontraram apoio entre as tribos locais e logo se reuniram em um só exército sob um chefe. Atuey—acho que esse era o nome dele. Eles o seguiram como sua última esperança. Mas nós os massacramos sem muita dificuldade. Atuey foi capturado e preparado para a execução. Quando o amarraram à cruz, pronto para ser queimado, um monge lhe ofereceu a verdadeira fé—disse que isso aliviaria seu sofrimento e lhe garantiria entrada no paraíso. Atuey perguntou ao monge se o paraíso estava aberto para espanhóis. E quando o monge respondeu que, claro, estava aberto para bons espanhóis, o cacique respondeu sem hesitar que, nesse caso, preferia o inferno—assim não teria que dividir o lar com gente tão cruel. Depois disso, disse mais algumas palavras em sua própria língua, e a fogueira foi acesa. Ele não fez um único som enquanto as chamas consumiam sua carne. Pelo mar, eu juro, não gostaria de presenciar algo assim na vida real. Meu sonho sempre termina do mesmo jeito: o capitão está sentado, imóvel. Só uma vela ao lado solta fumaça, e ele continua folheando um diário surrado. Devagar, como se cada palavra pesasse uma fortuna, murmurando algo para si mesmo. Mesmo nos meus sonhos, "+GetSexPhrase("cara","garota")+", eu entendo – é um sinal. Hora de sacar minha lâmina, porque ele já está atacando.\nAjude-me a pôr fim a esse pesadelo, Capitão. Venha comigo até a baía. Não vou lá sozinho – estou ficando sem pólvora. Mas antes de responder, preciso avisar: não posso te pagar. Se pudesse, já teria uma fila de ajudantes na porta. Só me resta contar com a ajuda de um companheiro de mar.";
			link.l1 = "Tudo bem, certo. Se ir até o navio vai te ajudar a se livrar desses sonhos e outras visões, eu vou te ajudar. Suba a bordo. Assim que eu terminar meus assuntos, vamos para a baía.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Aqui está... Já foi o orgulho da frota mercante espanhola, e agora não passa de um monte de tábuas podres mal se aguentando.";
				link.l1 = "Não é todo dia que se vê um gigante assim caído — estirado ali na praia. Como foi parar aqui?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Então vamos dar uma olhada por aqui. Quem sabe você realmente consiga encontrar alguma coisa.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Eu não quero parecer ingrato ou covarde... mas não me sinto seguro aqui agora. Vamos voltar quando o sol nascer.";
				link.l1 = "Certo, amigo, se você diz.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Zarpamos de Santiago rumo a Sevilha. Não levávamos muita carga, mas tínhamos um passageiro — um figurão, nada menos que um bispo. Pra ser sincero, a tripulação não ficou nada animada com essa viagem... mas quando é que alguém pergunta nossa opinião?\nNunca chegamos a alcançar o mar aberto. Perto de Turks, um brigue pirata nos atacou — rápido, ágil, armado até os dentes. Não era um bando de desordeiros, mas verdadeiros lobos do mar. No começo, o capitão quis fugir — não queria arriscar a vida do bispo. Mas com o vento daquele jeito, não dava pra voltar, e uma tempestade vinha do sul. Então não teve jeito — a luta começou.";
			link.l1 = "Ficar entre dois fogos é um destino miserável. E o que aconteceu depois?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "A luta não durou muito. Conseguimos derrubar o mastro de vante deles, mas os piratas revidaram à altura—uma bala de canhão perdida arrebentou a corda do leme e, como se o próprio diabo tivesse decidido, o navio ficou imóvel, a proa voltada para a tempestade que se aproximava. Ela vinha tão rápido que os piratas—que uma bala de corrente rasgue a vela-mestra deles—preferiram fugir, sumindo em uma das enseadas dos Turcos. E tudo o que podíamos fazer era esperar a tempestade nos engolir de vez. O capitão mandou arriar as velas e trocar a corda do leme, mas já era tarde demais.";
			link.l1 = "Então, a tempestade te pegou perto de Turks, te arrastou até aqui, e no fim te jogou na praia?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "That's exactly how it happened. The ship was pure chaos. The wind tore the rigging apart, masts crashed down one after another, smashing the deck and crushing people. If you didn't have time to tie yourself down, you were swept overboard; if you did, you were crushed by the wreckage. It was no better below deck—cannons, crates, cannonballs flew back and forth like demons, grinding up everything in their path. When we were finally thrown ashore, I was unconscious. I came to on the sand. Boatswain Sergio found me. He had two others with him.";
			link.l1 = "Não é muito, para um navio tão grande.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, capitão... Havia tantos corpos... Sabíamos na hora: não podíamos ficar ali. As ondas podiam levar o navio embora, e a gente junto. Perto dali, encontramos uma caverna—exaustos, caímos no sono assim que tocamos o chão. Quando acordei, não havia sinal do Sergio nem dos outros dois na caverna.\nProcurei por toda a praia, mas, por Deus, não estavam em lugar nenhum. Não dava pra voltar pro navio sozinho, então resolvi seguir para o interior. Foi assim que cheguei em Sharptown, onde, na minha própria burrice, só arrumei confusão.\nQueria saber qualquer coisa sobre os sobreviventes, então comecei a contar pra todo mundo o que tinha acontecido com a gente. Mas aqueles canalhas não estavam nem aí pra mim ou pra tripulação—só queriam saber do saque que podiam tirar do navio. A notícia se espalhou rápido pela ilha, e logo uma multidão desses ladrões já estava indo pra lá.";
			link.l1 = "Então, você ainda não sabe o que aconteceu com aquelas pessoas?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Voltar para o navio era perigoso demais. Qualquer um que tentasse se esgueirar para pegar algum saque podia acabar brigando pelo butim e meter uma bala em quem estivesse por perto... por acidente. Ou talvez — nada de acidente. Pelo mar, passei uma semana inteira escondido na taverna, interrogando todo mundo que tinha ido até a baía. Mas ninguém sabia de nada sobre minha tripulação, nem o que aconteceu com eles. No fim, tive que aceitar: parece que só eu sobrevivi àquela maldita tempestade. Talvez o destino tenha me favorecido mais do que aos outros. Ou talvez... tenha sido tudo graças ao amuleto que o jovem Capitão Eugenio de la Torre me deu um dia. Sempre mantive ele por perto. E, droga, parece que realmente me trouxe sorte.";
			link.l1 = "E onde ele está agora? Parece que isso não protege ele dos esqueletos, né...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Arrancaram do meu pescoço enquanto consertávamos a boca do poço no meu quintal. Um tronco bateu no meu pescoço e o amuleto caiu na água. O poço já estava cheio, e ninguém ia se dar ao trabalho de tirar tudo só por causa de um pingente.";
			link.l1 = "E desde então, você começou a ter pesadelos?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Caramba! Nunca tinha pensado nisso, mas foi exatamente o que aconteceu! Assim que terminamos de construir o poço, os pesadelos começaram.";
			link.l1 = "Que coincidência engraçada. Bem, agora você está aqui, exatamente como queria. Então, o que pretende fazer agora?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Eu não sei, Capitão... Eu não sei. Vamos dar uma olhada primeiro – a sensação de que tem algo que preciso encontrar aqui só ficou mais forte.";
			link.l1 = "Certo. Espero que não tenhamos vindo aqui à toa.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Escuta... Esse sentimento só fica mais forte. É como se eu estivesse a um passo de algo que preciso encontrar. Eu preciso embarcar naquele navio. Juro pelo mar, tem algo lá que vai explicar por que aquele maldito esqueleto não me deixa em paz.";
			link.l1 = "Então, talvez você não estivesse tão ansioso para chegar aqui à toa? Escondeu algo valioso no navio e agora voltou para buscar seu tesouro?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Que bobagem é essa? Você realmente acha que eu atravessaria o arquipélago inteiro por uns poucos dobrões depois de quarenta anos? Se você tivesse encontrado aquele esqueleto ao menos uma vez, nunca pensaria nisso.";
			link.l1 = "Certo, certo, se acalme. E como exatamente você pretende embarcar no navio?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "Tem uma porta escondida na popa. O capitão mesmo mandou fazer—caso um abordo dê errado pra gente. Que o raio me parta, não consigo passar esse meu corpo velho por ali sozinho, mas com nós dois...";
			link.l1 = "Certo, mostre o caminho e vamos acabar logo com isso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Bola de canhão no meu pescoço, que confusão! Ainda bem que esses aqui não foram tão ferozes quanto aquele que aparece toda manhã. Então, agora você acredita em mim?";
			link.l1 = "Depois de um espetáculo desses, é difícil *não* ficar. Você está bem?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Acho que sim. Malditos mortos-vivos... minhas pernas desabaram como mastros quebrados.";
			link.l1 = "Bem, se você está inteiro, não faz sentido ficar parado. Me dê sua mão, vou te ajudar a levantar.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Assim está melhor. Parece que não somos os primeiros a saber como entrar aqui.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Parece que esses são meus homens. Os que sobreviveram à tempestade... Reconheci o colete do Sergio — ou o que restou dele, pelo menos. Então eles voltaram — talvez procurando sobreviventes, ou para enterrar os mortos. Mas parece que aquele mesmo mal acabou com eles também.";
			link.l1 = "É estranho que só restaram pedaços do colete. Nada mais.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Nem sinal da batina do nosso passageiro — do bispo — restou. Pelo jeito, a chave apertada na mão daquele infeliz só pode ser dele. Ele nunca largava aquilo, nem por um instante. Parece que não teve mais sorte que os outros. Pelo visto, esses mortos-vivos não estavam vagando por aí à toa. Algo os mantém aqui... ou estão guardando alguma coisa.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Nem mesmo um traço da batina do bispo restou. Pelo jeito, essa chave apertada na mão desse pobre coitado deve ser dele. Ele nunca largava isso, nem por um segundo. Parece que não teve mais sorte que os outros. Pelo visto, esses mortos-vivos não estavam vagando por aqui à toa. Algo está prendendo eles aqui... ou estão guardando alguma coisa.";
			}
			link.l1 = "Agora estou com a sensação de que devemos encontrar alguma coisa aqui. Vamos acabar logo com isso — não quero ficar aqui um segundo a mais do que o necessário.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "Então, capitão, conseguiu encontrar alguma coisa?";
			link.l1 = "Parece que este era o baú do bispo. Achei algo dentro dele. Dá uma olhada.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez... Que o raio me parta... Eu já vi este diário nos meus sonhos! É exatamente o mesmo que o capitão folheava antes de...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Diabo, parece que ele está queimando minhas mãos!";
			link.l1 = "Queima suas mãos? Ah, qual é, é só um diário velho. Ou você realmente acredita que tem algum poder sombrio nele?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Juro por todos os santos, não estou brincando! Esse maldito diário parece que está queimando nas minhas mãos. Ele precisa ser destruído! Rasgue, queime, afogue—qualquer coisa! Não, espere... Melhor queimar. Isso, queime, para não sobrar nem cinza!";
			link.l1 = "Como quiser. Então vamos para a terra firme, acender uma fogueira e lançar essa crônica de malfeitos às chamas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Bem, é isso... Sinto como se um peso tivesse sido tirado do meu peito.";
			link.l1 = "Você acha que agora acabou tudo?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Quem sabe... Mas juro pelo mar, não me sentia tão leve há muito tempo. É como se uma velha dívida tivesse sido finalmente perdoada. Ainda assim... queria nunca ter visto aquele maldito diário. Ou descoberto o que estava escrito lá dentro.";
			link.l1 = "Não é de se admirar que você tenha tido esses sonhos. Mesmo que não estivesse envolvido nisso tudo, você é a única pessoa viva que, de alguma forma, tinha ligação com o diário.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Nem o ouro, nem a fé justificam o que fizeram sob o comando de Velasquez. E fico aliviado que tudo que pudesse nos lembrar disso tenha sido destruído pelo fogo. Certas coisas jamais deveriam cair nas mãos de quem possa se sentir tentado a repetir aquele exemplo.";
			link.l1 = "Velasquez é só um entre muitos. Quem sabe quantos outros diários assim circulam pela velha Europa, alimentando a ganância e a impunidade de novos conquistadores? Uma coisa é certa—este aqui não vai envenenar mais ninguém. Aliás, o baú do bispo guardava não só o diário, mas também um bom punhado de dobrões—trezentos ao todo. Metade deles é justamente sua.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velasquez pagou pelos seus pecados, e se alguém decidir seguir seus passos, terá o mesmo destino. Mais cedo ou mais tarde, o destino dá a cada um o que merece.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Se é assim - não vou recusar. Todo mundo precisa de dinheiro, e eu preciso agora mais do que nunca. Ninguém mais vai me aceitar como marinheiro - já estou velho demais pra isso. Então obrigado, Capitão, por não me mandar embora, como fizeram os outros.";
			link.l1 = "Eu admito, no começo sua história parecia delírio de um lunático. Mas você contou de um jeito tão convincente que, querendo ou não, a gente acaba acreditando. Ainda assim, o aparecimento daqueles nativos mortos-vivos me pegou de surpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Eu só queria ver se você tinha perdido o juízo. Sabe, não é tão fácil acreditar em histórias assim.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "Quero acreditar nisso... Mas, pelo mar, já vi muitos que a sorte protegeu, não importa quão sombrios fossem seus atos. Talvez a hora deles chegue—só que não aqui, mas no próprio caldeirão do diabo. E obrigado, Capitão. Por não se afastar, por ouvir, por me acompanhar até o fim. Isso significa muito, sabia.";
			link.l1 = "Eu admito, no começo sua história parecia delírio de um louco. Mas você contou de um jeito tão convincente que, querendo ou não, a gente acaba acreditando. Mesmo assim, a aparição daqueles índios mortos-vivos me pegou de surpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Eu só queria ver se você tinha enlouquecido. Sabe, não é fácil acreditar em histórias assim.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Agora você entende como me senti quando vi aqueles mortos-vivos pela primeira vez. Espero que eles tenham sumido de vez... Caso contrário, duvido que eu sobreviva a outro encontro daqueles.";
			link.l1 = "Bem, já que terminamos aqui, é hora de sair desse lugar. Suba a bordo, vou te deixar no porto de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Agora você entende como me senti quando vi aqueles mortos-vivos pela primeira vez. Espero que tenham ido embora de vez... Caso contrário, duvido que eu sobreviva a outro encontro como aquele.";
			link.l1 = "Bem, já que terminamos aqui, é hora de sair deste lugar. Suba a bordo, vou te deixar no porto de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Muito obrigado mais uma vez, Capitão "+GetFullName(pchar)+"  À beira-mar, aquela sensação estranha sumiu, e espero que tenha levado junto aquele maldito saco de ossos. Que tal tomarmos um gole, hein?";
			link.l1 = "Obrigado pelo convite, Gonzalo, mas estou com as mãos cheias agora. Quem sabe numa outra ocasião. Beba uma por nós dois.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Eu entendo. Mas deixe-me dizer uma coisa, Capitão: depois de tudo que passamos juntos, eu não poderia ir embora sem te agradecer. Não seria certo. Aqui, fique com isto. Na minha juventude, corri atrás de tesouros mais de uma vez, juro pelo mar. Mas agora minha saúde já não é a mesma, e minhas costas vivem me dando trabalho. Mas você—você é jovem, um marinheiro experiente. Vai encontrar isso com facilidade. Boa sorte para você, "+GetFullName(pchar)+", bons ventos e sete pés sob a quilha.";
				link.l1 = "Obrigado, Gonzalo. Boa sorte pra você também, adeus.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Então, está na hora de dizer adeus. Bons ventos e uma viagem segura, Capitão "+GetFullName(pchar)+"!";
				link.l1 = "Adeus, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}
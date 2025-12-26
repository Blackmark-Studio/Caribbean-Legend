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

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, dizem que Port-au-Prince perde seu encanto quando você não sorri. Hoje, ao que parece, é um desses dias. Perdoe minha franqueza, mas algo está lhe incomodando?";
			}
			else
			{
				link.l1 = "Mademoiselle, histórias sobre sua beleza e elegância chegaram aos meus ouvidos, e devo dizer—os boatos não fazem justiça a você. Também dizem que Port-au-Prince perde seu encanto quando você não sorri. Hoje, infelizmente, parece ser um desses dias. Diga o nome do canalha que ousou tirar seu ânimo, e juro que o desafio para um duelo só para ver o sorriso voltar ao seu lindo rosto.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, sua atenção é realmente comovente... Admito que sua preocupação me toca. Mas, infelizmente, a causa da minha tristeza não é algo que possa ser dissipado com uma simples conversa. Não é culpa de ninguém, mas sim das circunstâncias que, receio, estão além do que até mesmo os mais determinados podem superar.";
				link.l1 = "Circunstâncias? Eu lhe asseguro, mademoiselle, que "+GetFullName(pchar)+" nenhum obstáculo é intransponível. Conte-me o que aconteceu—talvez eu possa ajudar.";
			}
			else
			{
				dialog.text = "Oh, monsieur, você realmente é um mestre das palavras gentis. Confesso, você quase conseguiu me fazer sorrir. Mas, infelizmente, um duelo não resolveria meu problema. Quem escureceu meu dia não foi um vilão, mas sim as circunstâncias que nem mesmo um cavalheiro tão galante quanto você pode superar.";
				link.l1 = "Circunstâncias? Minha cara mademoiselle, Capitã "+GetFullName(pchar)+" posso enfrentar qualquer tempestade! E se eu falhar, juro pra você que vou comer o chapéu do primeiro que passar na minha frente!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Se você realmente insiste, vou lhe contar o que aconteceu. Mas antes, preciso da sua palavra de que essa conversa ficará só entre nós.";
				link.l1 = "Você tem minha palavra solene, mademoiselle. O que quer que me conte ficará só entre nós, mesmo que eu tenha que levar esse segredo para as profundezas do oceano.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", você certamente tem o dom de alegrar até a mais aflita das damas. Mas, por favor, tenha piedade dos chapéus dos inocentes que passam por aqui. Se você realmente insiste, vou contar o que aconteceu. Só me prometa que minhas palavras ficarão entre nós.";
				link.l1 = "Dou-lhe minha palavra, mademoiselle, que tudo o que me disser será mantido em absoluto sigilo, mesmo sob ameaça de morte.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Muito bem. Um colar desapareceu dos meus aposentos... mas entenda, ele é muito mais do que um simples enfeite. Foi um presente de alguém que ocupa um lugar especial no meu coração. Sua ausência dói como uma ferida, muito mais profunda do que a simples perda de um objeto\nPensei muito sobre quem poderia ser o responsável, e só cheguei a uma conclusão. Temo que deva ser um dos meus próprios criados. Só eles têm acesso aos meus aposentos privados e poderiam cobiçar uma peça tão valiosa. Mas não ouso fazer essa acusação em público...";
			link.l1 = "De fato, é uma questão bastante delicada, especialmente se a discrição é o que você deseja. Mas, para que eu possa ajudar, preciso entender o que te obriga a guardar esse segredo com tanto cuidado. Sem saber quais perigos enfrentamos, posso acabar nos colocando em risco sem querer. Diga-me de quem devemos nos manter longe e que ameaças se escondem nas sombras.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Não pode falar abertamente? Então receio, mademoiselle, que só posso lhe oferecer meus melhores votos. Não tenho gosto nem talento para intrigas e segredos. Na minha opinião, seu problema poderia ser resolvido rapidamente com a ajuda da guarda da cidade. Mas parece que você escolheu seguir um caminho mais perigoso por essas águas turbulentas.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Não consegue falar claramente? Então devo lhe pedir desculpas, mademoiselle, pois me sinto completamente impotente nesse nevoeiro de segredos. Não tenho apreço por assuntos clandestinos e negociações nas sombras. Seu dilema parece bastante simples: algo que a guarda da cidade poderia resolver facilmente. Mas você insiste em transformá-lo numa intriga digna das cortes reais da Europa.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "É assim que o famoso Capitão "+GetFullName(pchar)+" enfrenta adversidades? Fugindo ao primeiro sinal de dificuldade? Talvez seus talentos fossem mais úteis contando barris de rum ou trocando provocações com mercadores do cais. Peço apenas isto: se você tem um mínimo de honra, mantenha o que compartilhei em absoluto sigilo. Tenha um bom dia, Capitão.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "Você fala com sabedoria, "+GetAddress_Form(NPChar)+". A verdade, então: este colar veio de um homem cuja simples existência desperta a fúria do meu tio — o governador dos territórios franceses nesta ilha. Ele proibiu qualquer contato, até mesmo a menção do nome dessa pessoa. Se meu tio descobrir a origem deste presente, as consequências serão desastrosas, não só para mim, mas também para...";
			link.l1 = "Não diga mais nada, mademoiselle. Entendi perfeitamente. Fique tranquila, vou recuperar seu colar com total discrição, guardando seu segredo com o mesmo zelo de um dragão protegendo seu tesouro.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Você tem minha mais profunda gratidão, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+". Sua coragem e compreensão aquecem meu coração nestes tempos difíceis. Confio plenamente que meu segredo está seguro com você. Que os ventos da sorte encham suas velas nesta empreitada delicada.";
			if (pchar.sex == "woman")
			{
				link.l1 = "A sorte sorri para quem ousa agir, mademoiselle. Fique tranquila—vou recuperar seu colar, tão certo quanto a maré volta à praia.";
			}
			else
			{
				link.l1 = "A sorte sorri para quem tem coragem, mademoiselle. Assim que eu recuperar seu precioso colar, ele será devolvido às suas mãos graciosas, onde realmente pertence.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Capitão, você voltou! Tem notícias para mim? Espero que tenha recuperado meu colar. Por favor, diga que sim.";
				link.l1 = "Seus problemas acabaram, Julie. O colar foi recuperado, e é com grande satisfação que o devolvo ao seu devido lugar—suas delicadas mãos.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Capitão, você voltou! Tem notícias para mim? Espero que tenha recuperado meu colar. Por favor, diga que sim.";
				link.l1 = "Lamento desapontá-la, Julie. A busca continua. Mas anime-se—não vou descansar enquanto seu colar precioso não for devolvido a você.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "Saudações, monsieur. Que assuntos trazem você a bordo do nosso navio?";
			link.l1 = "I seek Captain Tristan Renier; I come bearing a proposition that would line his pockets handsomely.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Preciso falar com o Capitão Tristan Renier sobre um assunto delicado—uma questão pessoal, entende.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "O capitão foi para terra, infelizmente. Talvez você o encontre em algum lugar da cidade, se for algo urgente.";
			link.l1 = "Você sabe para onde ele foi? Tem algum lugar que ele costuma frequentar quando vem a este porto?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "O capitão foi para terra, infelizmente. Talvez você o encontre em algum lugar da cidade, se seu assunto for urgente.";
			link.l1 = "Você saberia para onde ele foi? Tem algum lugar que ele costuma frequentar quando está neste porto?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Me desculpe, "+GetAddress_Form(NPChar)+", mas o capitão prefere guardar para si seus motivos e destinos. Só sei que ele desembarcou há algumas horas.";
			link.l1 = "Mesmo assim, já ajuda bastante. Agradeço pela sua ajuda.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Quem diabos é você? Com que direito ousa invadir meus aposentos privados sem ser convidado?";
				link.l1 = "Eu sou o Capitão "+GetFullName(pchar)+". E eu venho por um assunto de certa importância.";
			}
			else
			{
				dialog.text = "E quem seria você, minha senhora? Não me lembro de ter feito convites para esta noite. Mas devo admitir, alguns visitantes inesperados acabam sendo mais... interessantes que outros. O que traz uma visão dessas aos meus modestos aposentos?";
				link.l1 = "Eu sou o Capitão "+GetFullName(pchar)+". E minha visita diz respeito a negócios, não a lazer.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Negócios, é isso? Que tipo de assunto poderia justificar uma interrupção tão descortês?";
				link.l1 = "É bem simples. Você está com um colar que eu vim buscar.";
			}
			else
			{
				dialog.text = "Negócios, você diz? Que interessante... Que assunto comercial tão urgente traria uma dama de tantos encantos até meus aposentos particulares?";
				link.l1 = "Poupe-me das suas palavras doces, monsieur. Vim buscar o colar que está com você. E sim, eu sei muito bem que ele está em suas mãos.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! Um colar, você diz? De fato, adquiri uma peça dessas recentemente, mas o que isso te interessa? Certamente não espera que eu entregue minha propriedade ao primeiro estranho que a exigir?";
			}
			else
			{
				dialog.text = "Um colar? De fato... Recentemente adquiri mesmo esse enfeite. E diga-me, capitão, como exatamente pretende tomar de mim esta joia que, por direito, me pertence?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Estou disposto a lhe oferecer cinco mil pesos pela peça. Uma quantia generosa que lhe permitiria comprar um ornamento igualmente belo, talvez até mais grandioso. Enquanto isso, este colar em especial seria devolvido a quem o valoriza acima de tudo—muito mais do que qualquer valor em dinheiro.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Vou falar claramente, senhor. Suas opções diminuíram bastante: entregue o colar de boa vontade e viva para navegar mais um dia, ou resista e terei que tirá-lo do seu corpo sem vida. A decisão é sua, mas recomendo que não demore a escolher.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "Cinco mil, é isso? Pois bem, Capitão, você sabe negociar como poucos. Aqui, leve a bugiganga se ela é tão importante assim.";
				link.l1 = "Sua sabedoria é tão grande quanto sua generosidade, senhor. Essa decisão não será motivo de arrependimento.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				Notification_Skill(true, 25, SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Eu não adquiri este colar para trocá-lo com o primeiro vagabundo que aparecer com moedas! É um presente para minha esposa, e não quero mais ouvir sobre isso. Saia da minha presença antes que eu chame homens para te tirar daqui!";
				link.l1 = "Se você recusar um acordo de cavalheiros, então vou buscar o que quero por meios menos civilizados.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				Notification_Skill(false, 25, SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Seu insolente... Acha mesmo que suas ameaças de criança vão me assustar? Ha! Você não faz ideia de com quem está lidando!";
				link.l1 = "Eu não me importo com quem você é. Apenas entregue o colar e eu vou embora. Ou será que você está mesmo disposto a morrer por uma bugiganga que não significa nada pra você?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Eu não comprei esse colar só para ficar discutindo com gente como você! Era um presente para minha esposa, e você não tem nada que se meter aqui. Saia antes que a gente te coloque pra fora!";
				link.l1 = "Se você não quiser entregar isso de boa, eu vou tomar à força.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Maldito seja você e esse colar amaldiçoado! Pegue. Pegue e saia daqui antes que eu mude de ideia.";
			link.l1 = "Uma decisão sábia! Adeus.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", você trouxe alegria de volta ao meu coração! Você não só devolveu o colar, mas também uma parte da minha alma. Sua nobreza é admirável, e prometo contar a todos que puder sobre o seu valor!";
			link.l1 = "Por favor, mademoiselle, não devolvi isso por fama. Seu sorriso é a única recompensa que realmente valorizo.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Você é tão modesto, "+pchar.name+". Mas, por favor, aceite este baú de dobrões. Só de saber que você aceitou meu presente vou sentir que te agradeci como você realmente merece.";
			link.l1 = "Por favor, mademoiselle, não insista. Suas palavras gentis significam mais para mim do que qualquer baú de dobrões.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Se isso lhe traz paz, mademoiselle, aceitarei seu presente. Mas saiba que não fiz isso por recompensa. "+GetSexPhrase("Seu reconhecimento","Sua gratidão")+" significa muito mais para mim do que esses dobrões.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "Eu acabei esquecendo de perguntar—você sabe quem roubou o colar?";
			link.l1 = " Tudo que eu sei, mademoiselle, é que um comerciante recebeu isso de alguém chamada Giselle. E, pelo jeito das coisas, essa pode não ser a última joia que ela pretende vender. ";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Eu esqueci completamente de perguntar—você sabe quem roubou o colar?";
			link.l1 = "Tudo o que sei, mademoiselle, é que um comerciante recebeu isso de alguém chamada Giselle. E, pelo que parece, essa pode não ser a última joia que ela pretende vender.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle? Mas ela é minha criada! Eu já desconfiava... mas não queria acreditar. O pior é que nem posso puni-la de verdade. Ela pode revelar meu segredo—e isso eu não posso permitir.";
			link.l1 = "E então, o que vai fazer? Vai deixar ela sair impune e continuar te roubando?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Ah não, claro que não. Primeiro, vou garantir que ela não chegue mais perto de mim. Depois, vou pensar em um jeito de puni-la de forma que pareça que a punição veio de outro lugar.";
			link.l1 = "A astúcia de uma mulher é uma arma perigosa, especialmente nas mãos de alguém tão refinada e perspicaz quanto você. Tenho certeza de que sua criada nem percebeu que o jogo já está perdido—e não a favor dela.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, capitão... Eu não gostaria de recorrer a truques, mas... às vezes, a astúcia é o único caminho possível.";
			link.l1 = "É verdade, Julie. Odeio ter que te deixar, mas o dever me chama. Quem mais, se não eu, vai cuidar da minha tripulação?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Até a próxima, "+pchar.name+". Por favor, visite nosso porto com mais frequência. Nossa cidade sente muita falta de "+GetSexPhrase("homens tão nobres e valentes como você.","mulheres de coração tão nobre e espírito tão corajoso, como o seu.")+"";
			link.l1 = "Você me lisonjeia, mademoiselle. Prometo que não vou perder nenhuma oportunidade de voltar à sua bela cidade. Até a próxima.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Que surpresa! Ainda conquistando os mares?";
						link.l1 = "Fico feliz em vê-la, mademoiselle. Vou conquistando, na medida do possível, embora o mar continue implacavelmente temperamental. E você—está aproveitando um pouco de paz e tranquilidade?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, Capitão "+pchar.lastname+", que alegria te ver de novo! Espero que esteja tudo bem com você?";
						link.l1 = "Fico muito feliz em vê-la também, mademoiselle. Os negócios, como sempre, exigem tempo e esforço, mas encontros como este iluminam qualquer dia. E como têm sido os seus dias?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitão "+pchar.lastname+", voltou de novo? Será que ainda existem pessoas na nossa humilde cidade que você não traiu por um punhado de moedas de ouro?";
						link.l1 = "Mademoiselle, eu entendo seus sentimentos, mas agi conforme achei correto. Às vezes, a decisão certa causa dor, e lamento que isso tenha te machucado.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Capitão "+pchar.lastname+", de novo? Sua ganância é tão sem limites que você não consegue deixar nossa cidade em paz e já está caçando sua próxima vítima?";
						link.l1 = "Mademoiselle, me desculpe se minhas ações te machucaram, mas agi de acordo com a minha consciência.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Ultimamente, as coisas têm estado calmas e tranquilas—nada perturba a paz. Por favor, visite nosso porto mais vezes, Capitão. Tenho certeza de que vai encontrar tudo o que deseja aqui, tanto na nossa loja quanto além dela.";
			link.l1 = "Obrigada, mademoiselle. Vou tentar passar aqui com mais frequência. Tenho certeza de que sua cidade ainda guarda muitas surpresas agradáveis.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "Graças a você, capitão, meus dias agora são muito mais tranquilos. Espero mesmo que volte a nos visitar.";
			link.l1 = "Claro, mademoiselle. Sua cidade sempre deixa a melhor impressão. Até a próxima.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Capitão "+pchar.lastname+", nos encontramos de novo. Impressionante, não acha?";
					link.l1 = "Parece que o destino está sorrindo para nossos encontros hoje, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Capitão "+pchar.lastname+", parece que nossos caminhos se cruzaram mais uma vez.";
					link.l1 = "De fato, senhorita. Fico feliz em vê-la novamente.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Parece que estamos nos encontrando até demais, capitão. Ou será que você simplesmente não consegue ficar longe daqueles que já traiu?";
					link.l1 = "Mademoiselle, nossos encontros são pura coincidência, mas entendo sua amargura. Só espero que um dia você compreenda meus motivos.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "O que você quer agora? Sua sorte não pode ser tão ruim a ponto disso ser só coincidência. Ou veio só pra me lembrar da sua desgraça?";
					link.l1 = "Mademoiselle, não tive intenção de incomodar ou reabrir feridas antigas. Este encontro foi realmente um acaso.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}